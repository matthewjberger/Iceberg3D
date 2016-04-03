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

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
    ~Mesh();

    void draw(const ShaderProgram *shaderProgram = nullptr) const;
    void setup_mesh();

private:

    void free();

    VAO meshVAO_;
    VBO meshVBO_;
    VBO meshIBO_;

    std::vector<Vertex> vertices_;
    std::vector<GLuint> indices_;
    std::vector<Texture> textures_;
};

#endif

