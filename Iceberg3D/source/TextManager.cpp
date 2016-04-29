#include "TextManager.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

typedef unsigned char BYTE;

using namespace iceberg;
using namespace utility;

TextManager::TextManager(Game* game)
{
    fontLoaded_ = false;
    currentFont_ = "";

    const int NUM_CORNERS = 4;

    const std::string vertexShader = 
        "#version 330 core\n"
        "layout (location = 0) in vec4 v_Data;\n"
        "out vec2 f_texCoord;\n"
        "uniform mat4 projection;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projection * vec4(v_Data.xy, 0.0f, 1.0f); \n"
        "   f_texCoord = vec2(v_Data.z, 1.0f - v_Data.w); // necessary to flip texture\n"
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

    textVAO_ = std::make_shared<VAO>();
    // 4 corners of the glyph's quad; 4 floats per vertex (x,y,u,v)
    textVBO_ = std::make_shared<Buffer>(NUM_CORNERS * sizeof(glm::vec4));
    textIBO_ = std::make_shared<Buffer>(6 * sizeof(GLuint));

    // Specify texture coordinates
    glm::vec2 quadUVCoords[] =
    {
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f)
    };

    // Specify indices
    GLuint indices[] =
    {
        1, 2, 0, // First triangle
        2, 1, 3  // Second Triangle
    };

    textVAO_->bind();

        // VBO
        textVBO_->bind();
        for (int i = 0; i < NUM_CORNERS; i++)
        {
            // The x and y coords will be updated later
            glm::vec4 data = glm::vec4(0.0f, 0.0f, quadUVCoords[i]);
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

void TextManager::load_font(const std::string& path, int scale)
{
    // TODO: Scale by dpi instead of by pixels using font metrics
    // TODO: Check if path exists and handle error

    // Retrieve the font name
    std::string fontName = path.substr(path.find_last_of('/') + 1);

    // Strip the extension
    std::string extension = ".ttf";
    std::string::size_type extPos = fontName.find(extension);
    if(extPos != std::string::npos)
    {
        fontName.erase(extPos, fontName.length());
    }

    // Check if the font was already loaded
    if (fontCache_.find(fontName) != fontCache_.end())
    {
        currentFont_ = fontName;
        return; // The font was found in the font cache
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    auto bytes = ReadAllBytes(path.c_str());
    unsigned char* data = bytes.data(); // needs one level of indirection to work properly

    stbtt_fontinfo fontInfo;
    stbtt_InitFont(&fontInfo, data, 0);

    Font font;

    // Generate bitmaps for ASCII 32 (space) - ASCII 126 (~)
    for(size_t codepoint = 32; codepoint <= 126; codepoint++)
    {
        // Create the glyph texture
        GlyphInfo *glyphInfo = new GlyphInfo;
        unsigned char *bitmap = stbtt_GetCodepointBitmap(&fontInfo, 0, stbtt_ScaleForPixelHeight(&fontInfo, scale), codepoint, &glyphInfo->size.x, &glyphInfo->size.y, 0, 0);
        glyphInfo->texture.create_from_data(glyphInfo->size.x, glyphInfo->size.y, bitmap, GL_RED);

        // Get the glyph metrics
        stbtt_GetCodepointHMetrics(&fontInfo, codepoint, &glyphInfo->advance, &glyphInfo->bearing.x);
        glyphInfo->bearing.y = 0; // TODO: Figure out how to load this metric
        glyphInfo->scale = scale;

        // Add the glyph to the font
        font.insert(std::pair<char, GlyphInfo*>(char(codepoint), glyphInfo));
    }

    // Add the font to the font cache by name
    fontCache_.insert(std::pair<std::string,Font>(fontName, font));

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    currentFont_ = fontName;
    fontLoaded_ = true;
}

void TextManager::RenderText(const std::string& text, int xPos, int yPos, glm::vec3 color)
{
    glm::vec2 quadUVCoords[] =
    {
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f)
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // TODO: Add a more robust failure condition here
    if (!fontLoaded_) return;
    shaderProgram_->use();
    shaderProgram_->set_uniform("color", color);
    textVAO_->bind();

        /* Vertices must go in this order */
        int advance = 0;
        std::string::const_iterator letter;
        for( letter = text.begin(); letter != text.end(); letter++)
        {
            /* IMPORTANT! */
            // TODO: Use glyph metrics to space out letters correctly

            auto glyph = fontCache_[currentFont_][*letter];
            glm::vec2 quadVertices[] =
            {
                // Top Left
                glm::vec2(xPos, yPos),

                // Top Right
                glm::vec2(xPos + glyph->size.x, yPos),

                // Bottom Left
                glm::vec2(xPos, yPos - glyph->size.y),

                // Bottom Right
                glm::vec2(xPos + glyph->size.x, yPos - glyph->size.y)
            };            

            textVBO_->bind();
            for (int i = 0; i < 4; i++)
            {
                glm::vec4 quadInfo(quadVertices[i], quadUVCoords[i]);
                textVBO_->update_buffer(&quadInfo, sizeof(glm::vec4), sizeof(glm::vec4) * i);
            }
            textVBO_->unbind();

            glyph->texture.bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 6 indices
        }

    textVAO_->unbind();
    shaderProgram_->disuse();

    glDisable(GL_BLEND);
}