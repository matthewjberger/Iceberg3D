#ifndef __MODEL_H
#define __MODEL_H

#include "../core/GlobalIncludes.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Mesh.h"

class Model
{
    public:
        Model(std::string path, std::string texturePath = "", bool genMipMaps = true);
        ~Model();

        void Draw();
        void LoadTexture(std::string image, bool genMipMaps);
        void Free();

        void Scale(glm::vec3 scale);
        void Scale(glm::mat4 base, glm::vec3 scale);

        void Rotate(float angle_in_degrees, glm::vec3 rotationAxes);
        void Rotate(glm::mat4 base, float angle_in_degrees, glm::vec3 rotationAxes);

        void Translate(glm::vec3 position);
        void Translate(glm::mat4 base, glm::vec3 position);

        void SetModelMatrix(glm::mat4 matrix);

        glm::mat4 GetModelMatrix();
        btCollisionShape* GetCollisionShape();

    private:

        glm::mat4 modelMatrix;

        std::string directory;
        std::vector<Mesh> meshes;

        void LoadModel(std::string path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh);

        Texture texture;
        bool textureLoaded;

        // TODO: move this triangle mesh to the mesh class
        // return a vector of triangle meshes corresponding to the loaded model's internal meshes
        btTriangleMesh* collisionMesh;
        btCollisionShape* collisionShape;
};

#endif
