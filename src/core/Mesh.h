#ifndef __MESH_H
#define __MESH_H

#include "GlobalIncludes.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "Texture.h"

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
        void Draw();

        void SetupMesh();
        void Free();

    private:
        VAO meshVAO;
        VBO meshVBO;
};

#endif
