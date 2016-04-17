#ifndef MODEL_H
#define MODEL_H

#include "GlobalIncludes.h"
#include "Texture.h"
#include "Mesh.h"
#include "TransformManager.h"
#include "Camera.h"

class Model
{
public:
    Model(const std::string &path);
    ~Model();

    void draw(const ShaderProgram* shaderProgram, const Camera* camera);

    TransformManager* transform_manager() const;

private:

    std::string directory_;
    std::vector<Mesh> meshes_;
    std::shared_ptr<TransformManager> transformManager_;

    std::vector<Tex> textureCache_;

    void load_model(const std::string &path);
    void process_node(aiNode* node, const aiScene* scene);
    Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Tex> load_textures(aiMaterial* material, aiTextureType type);
    int load_texture(const std::string &path) const;
};

#endif
