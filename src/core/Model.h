#ifndef __MODEL_H
#define __MODEL_H

#include "../core/GlobalIncludes.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Mesh.h"

class Model
{
    public:
        Model(std::string path);
        ~Model();

        void Draw();
        void LoadTexture(std::string image, bool genMipMaps);
        void Free();

    private:

        std::string directory;
        std::vector<Mesh> meshes;

        void LoadModel(std::string path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh);

        Texture texture;
        bool textureLoaded;
};

#endif
