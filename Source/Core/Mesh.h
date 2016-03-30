#ifndef MESH_H
#define MESH_H

#include "GlobalIncludes.h"
#include "VAO.h"
#include "VBO.h"

struct Vertex
{
    glm::vec3 Position;
    glm::vec2 TexCoords;
    glm::vec3 Normal;
};

class Mesh
{
public:
    // Mesh Data
    std::vector<Vertex> vertices;

    // Functions
    Mesh(std::vector<Vertex> _vertices);
    ~Mesh();

    void draw() const;

    void setup_mesh();
    void free();

private:
    VAO meshVAO;
    VBO meshVBO;
};

#endif

