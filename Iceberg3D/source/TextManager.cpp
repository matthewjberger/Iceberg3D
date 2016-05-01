#include "TextManager.h"

typedef unsigned char BYTE;

using namespace iceberg;
using namespace utility;

TextManager::TextManager(Game* game) : game_(game)
{
    fontLoaded_ = false;
    currentFont_ = "";

    create_shaders();

    textVAO_ = std::make_shared<VAO>();
    // 4 corners of the glyph's quad; 4 floats per vertex (x,y,u,v)
    textVBO_ = std::make_shared<Buffer>(4 * sizeof(glm::vec4));
    textIBO_ = std::make_shared<Buffer>(6 * sizeof(GLuint));

    // Specify texture coordinates
    quadUVCoords_.push_back(glm::vec2(0.0f, 1.0f));
    quadUVCoords_.push_back(glm::vec2(1.0f, 1.0f));
    quadUVCoords_.push_back(glm::vec2(0.0f, 0.0f));
    quadUVCoords_.push_back(glm::vec2(1.0f, 0.0f));

    // Specify indices
    GLuint indices[] =
    {
        1, 2, 0, // First triangle
        2, 1, 3  // Second Triangle
    };

    textVAO_->bind();

        // VBO
        textVBO_->bind();
        for (int i = 0; i < 4; i++)
        {
            // The x and y coords will be updated in the buffer later
            glm::vec4 data = glm::vec4(0.0f, 0.0f, quadUVCoords_[i]);
            textVBO_->add_data(&data, sizeof(glm::vec4));
        }
        textVBO_->upload_data(GL_DYNAMIC_DRAW);

        // IBO
        textIBO_->bind(GL_ELEMENT_ARRAY_BUFFER);
        textIBO_->add_data(&indices, sizeof(indices));
        textIBO_->upload_data();

        // Configuring vertex attributes must be done last
        textVAO_->enable_attribute(0); // Position and UV Coords bundled
        textVAO_->configure_attribute(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);

    textVAO_->unbind();

    shaderProgram_->use();
        glm::mat4 projection = glm::ortho(0.0f, game->screen_dimensions().y, 0.0f, game->screen_dimensions().x);
        shaderProgram_->set_uniform("projection", projection);
    shaderProgram_->disuse();
}

TextManager::~TextManager()
{
}

void TextManager::create_shaders()
{
    const std::string vertexShader =
        "#version 330 core\n"
        "layout (location = 0) in vec4 v_Data;\n"
        "out vec2 f_texCoord;\n"
        "uniform mat4 projection;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projection * vec4(v_Data.xy, 0.0f, 1.0f); \n"
        "   f_texCoord = vec2(v_Data.z, v_Data.w);\n"
        "}\n";

    const std::string fragmentShader =
        "#version 330 core\n"
        "in vec2 f_texCoord;\n"
        "out vec4 fragColor;\n"
        "uniform sampler2D glyphTexture;\n"
        "uniform vec3 color;\n"
        "void main()\n"
        "{\n"
        "    fragColor = vec4(color, texture(glyphTexture, f_texCoord).r); // use only the r channel\n"
        "}\n";

    shaderProgram_ = std::make_shared<ShaderProgram>();
    shaderProgram_->create_program();
    shaderProgram_->add_shader_from_source(vertexShader, GL_VERTEX_SHADER);
    shaderProgram_->add_shader_from_source(fragmentShader, GL_FRAGMENT_SHADER);
    shaderProgram_->link_program();
}

std::string TextManager::retrieve_font_name(const std::string& path) const
{
    std::string fontName = path.substr(path.find_last_of('/') + 1);
    std::string extension = ".ttf";
    std::string::size_type extPos = fontName.find(extension);
    if(extPos != std::string::npos)
    {
        fontName.erase(extPos, fontName.length());
    }
    else
    {
        game_->handle_error("Tried to load an invalid font:\n" + path);
    }
    return fontName;
}

bool TextManager::font_exists(const std::string& fontName) const
{
    return (fontCache_.find(fontName) != fontCache_.end());
}

void TextManager::load_font(const std::string& path, int size)
{
    std::string fontName = retrieve_font_name(path);

    if(font_exists(fontName))
    {
        use_font(fontName);
        return;
    }

    if (FT_Init_FreeType(&freeTypeInstance))
    {
        game_->handle_error("Could not initialize FreeType Library.");
    }

    // 4 bytes per pixel (32bpp) is OpenGL's default unpacking alignment
    // Freetype uses single channel bitmaps so only 1 byte per pixel is needed
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    FT_Face face;
    if(FT_New_Face(freeTypeInstance, path.c_str(), 0, &face))
    {
        game_->handle_error("Error loading ttf font:\n" + path);
    }

    // Setting width to 0 here tells FreeType
    // to dynamically calculate the width based on the given height
    FT_Set_Pixel_Sizes(face, 0, size);

    Font font;

    for(size_t codepoint = 32; codepoint <= 126; codepoint++)
    {
        // FT_LOAD_RENDER will tell FreeType
        // to create an 8bpp grayscale bitmap image
        if(FT_Load_Char(face, codepoint, FT_LOAD_RENDER)) // Loads in face->glyph
        {
            game_->handle_error("Error loading ttf font glyph:\n'" + char(codepoint) + '\'');
        }

        GlyphInfo *glyphInfo = new GlyphInfo();

        glyphInfo->bearing.x = face->glyph->bitmap_left;
        glyphInfo->bearing.y = face->glyph->bitmap_top;
        glyphInfo->advance = face->glyph->advance.x;

        int width = face->glyph->bitmap.width;
        int height = face->glyph->bitmap.rows;

        glyphInfo->texture.create_from_data(width, height, face->glyph->bitmap.buffer, GL_RED);

        // Add the glyph to the font
       font.insert(GlyphEntry(char(codepoint), glyphInfo));
    }

    // Add the font to the font cache by name
    fontCache_.insert(FontEntry(fontName, font));

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    currentFont_ = fontName;
    fontLoaded_ = true;

    FT_Done_Face(face);
    FT_Done_FreeType(freeTypeInstance);
}

void TextManager::render_text(const std::string& text, int xPos, int yPos, int scale, glm::vec3 color)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (!fontLoaded_)
    {
        game_->handle_error("Tried to render a string without a font loaded.");
    }

    shaderProgram_->use();
    shaderProgram_->set_uniform("color", color);
    std::string::const_iterator letter;
    for (letter = text.begin(); letter != text.end(); ++letter)
    {
        auto glyph = fontCache_[currentFont_][*letter];

        GLfloat x = xPos + glyph->bearing.x * scale;
        GLfloat y = yPos - (glyph->texture.dimensions().y - glyph->bearing.y) * scale;
 
        GLfloat width = glyph->texture.dimensions().x * scale;
        GLfloat height = glyph->texture.dimensions().y * scale;

        glm::vec2 quadVertices[] =
        {
            // Top Left
            glm::vec2(x, y),

            // Top Right
            glm::vec2(x + width, y),

            // Bottom Left
            glm::vec2(x, y + height),

            // Bottom Right
            glm::vec2(x + width, y + height)
        };

        textVBO_->bind();
        for (int i = 0; i < 4; i++)
        {
            glm::vec4 quadInfo(quadVertices[i], quadUVCoords_[i]);
            textVBO_->update_buffer(&quadInfo, sizeof(glm::vec4), sizeof(glm::vec4) * i);
        }
        textVBO_->unbind();

        glyph->texture.bind();
        textVAO_->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 6 indices
        textVAO_->unbind();

        xPos += (glyph->advance >> 6) * scale;
    }

    shaderProgram_->disuse();

    glDisable(GL_BLEND);
}

void TextManager::use_font(const std::string& fontName)
{
    currentFont_ = fontName;
}
