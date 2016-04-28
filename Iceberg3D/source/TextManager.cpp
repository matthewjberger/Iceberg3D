#include "TextManager.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
typedef unsigned char BYTE;

using namespace iceberg;

TextManager::TextManager()
{
    fontLoaded_ = false;
    currentFont_ = "";

    const std::string vertexShader = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 v_position;\n"
        "layout (location = 1) in vec2 v_texCoord;\n"
        "out vec2 f_texCoord;\n"
        "uniform mat4 mvpMatrix;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = mvpMatrix * vec4(v_position, 1.0f); \n"
        "   f_texCoord = vec2(v_texCoord.x, 1.0 - v_texCoord.y); // necessary to flip texture\n"
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

    shaderProgram_ = std::make_unique<ShaderProgram>();
    shaderProgram_->create_program();
    shaderProgram_->add_shader_from_source(vertexShader, GL_VERTEX_SHADER);
    shaderProgram_->add_shader_from_source(fragmentShader, GL_FRAGMENT_SHADER);
    shaderProgram_->link_program();

    textVAO = std::make_unique<VAO>();
    textVBO = std::make_unique<VBO>();
    textVBO = std::make_unique<VBO>();
}

TextManager::~TextManager()
{
}

void TextManager::load_font(const std::string& path, int scale)
{
    // TODO: Scale by dpi instead of by pixels using font metrics

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

    auto bytes = Utility::ReadAllBytes(path.c_str());
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

        // Add the glyph to the font
        font.insert(std::pair<char, GlyphInfo*>(char(codepoint), glyphInfo));
    }

    // Add the font to the font cache by name
    fontCache_.insert(std::pair<std::string,Font>(fontName, font));

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    currentFont_ = fontName;
}