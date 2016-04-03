#ifndef MODEL_H
#define MODEL_H

#include "../Core/GlobalIncludes.h"
#include "Texture.h"
#include "Mesh.h"

class Model
{
public:
    Model(const std::string &path);
    ~Model();

    void draw(const ShaderProgram* shaderProgram);
    void free();

    // Transformations
    void scale(glm::vec3 scale);
    void scale(glm::mat4 base, glm::vec3 scale);

    void rotate(float angle_in_degrees, glm::vec3 rotationAxes);
    void rotate(glm::mat4 base, float angle_in_degrees, glm::vec3 rotationAxes);

    void translate(glm::vec3 position);
    void translate(glm::mat4 base, glm::vec3 position);

    // Useful for moving a model using bullet physics
    void assign_model(glm::mat4 matrix);

    glm::mat4 model_matrix() const;
    btCollisionShape* collision_shape() const;

private:

    glm::mat4 modelMatrix_;

    std::string directory_;
    std::vector<Mesh> meshes_;

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
