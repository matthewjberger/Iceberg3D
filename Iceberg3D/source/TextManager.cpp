#include "TextManager.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
typedef unsigned char BYTE;

using namespace iceberg;

TextManager::TextManager()
{
}

TextManager::~TextManager()
{
}

void TextManager::load_font(const std::string& path, int scale)
{
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
    if (fontCache_.find(fontName) != fontCache_.end()) return; // The font was found in the font cache

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
        GlyphInfo glyphInfo;
        unsigned char *bitmap = stbtt_GetCodepointBitmap(&fontInfo, 0, stbtt_ScaleForPixelHeight(&fontInfo, scale), codepoint, &glyphInfo.size.x, &glyphInfo.size.y, 0, 0);
        glyphInfo.texture.create_from_data(glyphInfo.size.x, glyphInfo.size.y, bitmap, GL_RED);

        // Get the glyph metrics
        stbtt_GetCodepointHMetrics(&fontInfo, codepoint, &glyphInfo.advance, &glyphInfo.bearing.x);
        glyphInfo.bearing.y = 0; // TODO: Figure out how to load this metric

        // Add the glyph to the font
        font.insert(std::pair<char, GlyphInfo>(char(codepoint), glyphInfo));
    }

    // Add the font to the font cache by name
    fontCache_.insert(std::pair<std::string,Font>(fontName, font));

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}