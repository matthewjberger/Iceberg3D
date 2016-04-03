#ifndef MODEL_H
#define MODEL_H

#include "../Core/GlobalIncludes.h"
#include "Texture.h"
#include "Mesh.h"
#include "TransformManager.h"

class Model
{
public:
    Model(const std::string &path);
    ~Model();

    void draw(const ShaderProgram* shaderProgram);
    void free();

    btCollisionShape* collision_shape() const;

    TransformManager* transform_manager() const;

private:

    std::string directory_;
    std::vector<Mesh> meshes_;
    std::shared_ptr<TransformManager> transformManager_;

    void load_model(const std::string &path);
    void process_node(aiNode* node, const aiScene* scene);
    Mesh process_mesh(aiMesh* mesh, const aiScene* scene) const;
    static std::vector<Texture> load_textures(aiMaterial* material, aiTextureType type);

    Texture texture_;
    bool textureLoaded_;

    // TODO: Move this triangle mesh to the mesh class
    // return a vector of triangle meshes corresponding to the loaded model's internal meshes
    btTriangleMesh* collisionMesh_;
    btCollisionShape* collisionShape_;
};

#endif
