#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include "GlobalIncludes.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "VAO.h"
#include "Game.h"

namespace iceberg
{
    struct GlyphInfo
    {
        Texture texture;
        glm::ivec2 bearing;
        int advance;
    };

    using GlyphEntry = std::pair<GLchar, GlyphInfo*>;
    using Font = std::map<GLchar, GlyphInfo*>;
    using FontEntry = std::pair<std::string, Font>;
    using FontCache = std::map<std::string, Font>;

    class ICEBERGAPI TextManager
    {
    public:
        TextManager(Game* game);
        ~TextManager();

        void load_font(const std::string& path, int size);
        void use_font(const std::string& fontName);

        // Uses the default orthographic, 2D text shader
        void RenderText(const std::string& text, int xPos, int yPos, int scale = 1.0f, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));

    private:

        Game* game_;

        void create_shaders();
        std::string retrieve_font_name(const std::string& path) const;
        bool font_exists(const std::string& fontName) const;

        FT_Library freeTypeInstance;

        FontCache fontCache_;
        std::shared_ptr<ShaderProgram> shaderProgram_;
        std::string currentFont_;
        bool fontLoaded_;

        std::vector<glm::vec2> quadUVCoords_;

        std::shared_ptr<VAO> textVAO_;
        std::shared_ptr<Buffer> textVBO_;
        std::shared_ptr<Buffer> textIBO_;

    };
}
#endif