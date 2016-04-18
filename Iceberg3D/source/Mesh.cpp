#include "Mesh.h"
using namespace std;

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, const vector<Texture*>& textures)
{
    vertices_ = vertices;
    indices_ = indices;
    textures_ = textures;

    meshVAO_ = make_shared<VAO>();
    meshVBO_ = make_shared<VBO>();
    meshIBO_ = make_shared<VBO>();

    setup_mesh();
    build_collision_shape();
}

Mesh::~Mesh()
{
}

void Mesh::draw(const ShaderProgram* shaderProgram) const
{
    int diffuseCount = 1;
    int specularCount = 1;
    int textureCount = 0;
    string name;
    for (auto const& texture : textures_)
    {
        if (texture->type() == aiTextureType_DIFFUSE)
        {
            name = "texture_diffuse" + to_string(diffuseCount++);
        }
        else if (texture->type() == aiTextureType_SPECULAR)
        {
            name = "texture_specular" + to_string(specularCount++);
        }
        else
        {
            // Other kinds of texture maps are not handled yet
            continue;
        }
        shaderProgram->set_uniform(name, textureCount);
        texture->bind(textureCount++);
    }

    shaderProgram->use();
    meshVAO_->bind();
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
    meshVAO_->unbind();

    for(auto const& texture : textures_)
    {
        texture->unbind();
    }
}

void Mesh::setup_mesh()
{
    meshVAO_->create();
    meshVBO_->create();
    meshIBO_->create();

    meshVAO_->bind();

    // Add vertices
    meshVBO_->bind();
    meshVBO_->add_data(&vertices_.front(), sizeof(Vertex) * vertices_.size());
    meshVBO_->upload_data();

    // Add indices 
    meshIBO_->bind(GL_ELEMENT_ARRAY_BUFFER);
    meshIBO_->add_data(&indices_.front(), sizeof(GLuint) * indices_.size());
    meshIBO_->upload_data();

    // Vertex Positions
    meshVAO_->enable_attribute(0);
    meshVAO_->configure_attribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    // Vertex Normal Coordinates
    meshVAO_->enable_attribute(1);
    meshVAO_->configure_attribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

    // Vertex Texture Coordinates
    meshVAO_->enable_attribute(2);
    meshVAO_->configure_attribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tex_coords));

    meshVAO_->unbind();
}

void Mesh::build_collision_shape()
{
    collisionMesh_ = make_shared<btTriangleMesh>();
    btVector3 triArray[3];
    for(size_t i = 2; i < indices_.size(); i += 3)
    {
        int currentIndex = indices_[i];
        triArray[0] = btVector3(vertices_[currentIndex - 2].position.x,
                                vertices_[currentIndex - 2].position.y,
                                vertices_[currentIndex - 2].position.z);

        triArray[1] = btVector3(vertices_[currentIndex - 1].position.x,
                                vertices_[currentIndex - 1].position.y,
                                vertices_[currentIndex - 1].position.z);

        triArray[2] = btVector3(vertices_[currentIndex].position.x,
                                vertices_[currentIndex].position.y,
                                vertices_[currentIndex].position.z);

        collisionMesh_->addTriangle(triArray[0], triArray[1], triArray[2]);
    }
    collisionShape_ = make_shared<btBvhTriangleMeshShape>(collisionMesh_.get(), true);
}
