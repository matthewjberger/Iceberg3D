#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include "GlobalIncludes.h"
#include "Texture.h"

namespace iceberg
{
    struct GlyphInfo
    {
        Texture texture;
        glm::ivec2 size;
        glm::ivec2 bearing;
        int advance;
    };

    typedef std::map<GLchar, GlyphInfo> Font;
    typedef std::map<std::string, Font> FontCache;

    class ICEBERGAPI TextManager
    {
    public:
        TextManager();
        ~TextManager();

        void load_font(const std::string& path, int scale);

        FontCache fontCache_;

    private:


    };
}
#endif