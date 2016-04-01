#include "Mesh.h"
using namespace std;

Mesh::Mesh(vector<Vertex> _vertices)
{
    vertices = _vertices;
}

Mesh::~Mesh()
{
    free();
}

void Mesh::draw() const
{
    // Render the mesh
    meshVAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    meshVAO.unbind();
}

void Mesh::setup_mesh()
{
    meshVAO.create();
    meshVBO.create();

    meshVAO.bind();

    meshVBO.bind();
    meshVBO.add_data(&vertices.front(), sizeof(Vertex) * vertices.size());
    meshVBO.upload_data();

    // Vertex Positions
    meshVAO.enable_attribute(0);
    meshVAO.configure_attribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    // Vertex Normal Coordinates
    meshVAO.enable_attribute(1);
    meshVAO.configure_attribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

    // Vertex Texture Coordinates
    meshVAO.enable_attribute(2);
    meshVAO.configure_attribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

    meshVAO.unbind();
}

void Mesh::free()
{
    meshVAO.free();
    meshVBO.free();
}

