#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include "GlobalIncludes.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "VBO.h"
#include "VAO.h"

namespace iceberg
{
    struct GlyphInfo
    {
        Texture texture;
        glm::ivec2 size;
        glm::ivec2 bearing;
        int advance;
    };

    typedef std::map<GLchar, GlyphInfo*> Font;
    typedef std::map<std::string, Font> FontCache;

    class ICEBERGAPI TextManager
    {
    public:
        TextManager();
        ~TextManager();

        void load_font(const std::string& path, int scale);

        FontCache fontCache_;

    private:
        std::unique_ptr<ShaderProgram> shaderProgram_;
        std::string currentFont_;
        bool fontLoaded_;

        std::unique_ptr<iceberg::VAO> textVAO;
        std::unique_ptr<iceberg::VBO> textVBO;
        std::unique_ptr<iceberg::VBO> textIBO;

    };
}
#endif