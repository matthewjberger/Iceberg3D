#include "Mesh.h"
using namespace std;

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices)
{
    vertices_ = vertices;
    indices_ = indices;
}

Mesh::~Mesh()
{
    free();
}

void Mesh::draw() const
{
    meshVAO_.bind();
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
    meshVAO_.unbind();
}

void Mesh::setup_mesh()
{
    meshVAO_.create();
    meshVBO_.create();
    meshIBO_.create();

    meshVAO_.bind();

    // Add vertices
    meshVBO_.bind();
    meshVBO_.add_data(&vertices_.front(), sizeof(Vertex) * vertices_.size());
    meshVBO_.upload_data();

    // Add indices 
    meshIBO_.bind(GL_ELEMENT_ARRAY_BUFFER);
    meshIBO_.add_data(&indices_.front(), sizeof(GLuint) * indices_.size());
    meshIBO_.upload_data();

    // Vertex Positions
    meshVAO_.enable_attribute(0);
    meshVAO_.configure_attribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    // Vertex Normal Coordinates
    meshVAO_.enable_attribute(1);
    meshVAO_.configure_attribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

    // Vertex Texture Coordinates
    meshVAO_.enable_attribute(2);
    meshVAO_.configure_attribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tex_coords));

    meshVAO_.unbind();
}

void Mesh::free()
{
    meshVAO_.free();
    meshVBO_.free();
    meshIBO_.free();
}

