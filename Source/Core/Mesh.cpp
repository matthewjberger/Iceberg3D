#include "Mesh.h"
#include "Texture.h"
#include <sstream>
using namespace std;

Mesh::Mesh(vector<Vertex> _vertices)
{
    vertices = _vertices;
}

void Mesh::Draw()
{
    // Render the mesh
    meshVAO.Bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    meshVAO.Unbind();
}

void Mesh::SetupMesh()
{
    meshVAO.Create();
    meshVBO.Create();

    meshVAO.Bind();

        meshVBO.Bind();
        meshVBO.AddData(&vertices.front(), sizeof(Vertex) * vertices.size());
        meshVBO.UploadData();

        // Vertex Positions
        meshVAO.EnableAttribute(0);
        meshVAO.ConfigureAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

        // Vertex Texture Coordinates
        meshVAO.EnableAttribute(1);
        meshVAO.ConfigureAttribute(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

    meshVAO.Unbind();
}

void Mesh::Free()
{
    meshVAO.Free();
    meshVBO.Free();
}

