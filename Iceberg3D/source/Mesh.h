#ifndef MESH_H
#define MESH_H

#include "GlobalIncludes.h"
#include "VAO.h"
#include "VBO.h"
#include "Texture.h"
#include "ShaderProgram.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 tex_coords;
    glm::vec3 normal;
};

struct Tex
{
    GLuint id;
    aiTextureType type;
    aiString path;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Tex> textures);
    ~Mesh();

    void draw(const ShaderProgram *shaderProgram = nullptr) const;
    void setup_mesh();

private:

    void build_collision_shape();

    std::shared_ptr<VAO> meshVAO_;
    std::shared_ptr<VBO> meshVBO_;
    std::shared_ptr<VBO> meshIBO_;

    std::vector<Vertex> vertices_;
    std::vector<GLuint> indices_;
    std::vector<Tex> textures_;

    std::shared_ptr<btTriangleMesh> collisionMesh_;
    std::shared_ptr<btCollisionShape> collisionShape_;
};

#endif

