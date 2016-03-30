#include "Model.h"
using namespace std;

Model::Model(const string &path, const string &texturePath, bool genMipMaps)
{
    collisionMesh_ = new btTriangleMesh();

    textureLoaded_ = false;
    load_model(path.c_str());

    if (texturePath != "")
    {
        load_texture(texturePath, genMipMaps);
    }

    modelMatrix_ = glm::mat4(1.0f);
    collisionShape_ = new btBvhTriangleMeshShape(collisionMesh_, true);
}

Model::~Model()
{
    free();
}

void Model::free()
{
    for (GLuint i = 0; i < meshes_.size(); i++)
    {
        meshes_[i].free();
    }

    if (collisionMesh_ != nullptr)
    {
        delete collisionMesh_;
        collisionMesh_ = nullptr;
    }

    if (collisionShape_ != nullptr)
    {
        delete collisionShape_;
        collisionShape_ = nullptr;
    }
}

void Model::draw()
{
    for (GLuint i = 0; i < meshes_.size(); i++)
    {
        if (textureLoaded_)
        {
            texture_.bind();
        }
        meshes_[i].draw();
    }
}

void Model::load_model(const string &path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        printf("ERROR: Assimp - %s", importer.GetErrorString());
        return;
    }

    directory_ = path.substr(0, path.find_last_of('/'));
    process_node(scene->mRootNode, scene);
}

void Model::process_node(aiNode* node, const aiScene* scene)
{
    // Process all meshes_ in the node
    for (GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes_.push_back(process_mesh(mesh));
        meshes_.back().setup_mesh();
    }

    // Process all child nodes
    for (GLuint i = 0; i < node->mNumChildren; i++)
    {
        process_node(node->mChildren[i], scene);
    }
}

Mesh Model::process_mesh(aiMesh* mesh) const
{
    vector<Vertex> vertices;
    vector<GLuint> indices;
    btVector3 triArray[3];

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            aiVector3D position = mesh->mVertices[face.mIndices[j]];
            triArray[j] = btVector3(position.x, position.y, position.z);
            indices.push_back(face.mIndices[j]);
        }
        collisionMesh_->addTriangle(triArray[0], triArray[1], triArray[2]);
    }

    for (unsigned int i = 0; i < indices.size(); i++)
    {
        const aiVector3D* temp = &(mesh->mVertices[indices[i]]);
        Vertex v;
        v.Position.x = temp->x;
        v.Position.y = temp->y;
        v.Position.z = temp->z;

        // Texture Coordinates
        if (mesh->HasTextureCoords(0))
        {
            v.TexCoords = glm::vec2(mesh->mTextureCoords[0][indices[i]].x, mesh->mTextureCoords[0][indices[i]].y);
        }
        else
        {
            v.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(v);
    }

    return Mesh(vertices);
}

void Model::load_texture(const string &imagePath, bool genMipMaps)
{
    texture_.load(imagePath, genMipMaps);
    textureLoaded_ = true;
}

void Model::rotate(float angle_in_degrees, glm::vec3 rotationAxes)
{
    modelMatrix_ = glm::rotate(modelMatrix_, angle_in_degrees, rotationAxes);
}

void Model::rotate(glm::mat4 base, float angle_in_degrees, glm::vec3 rotationAxes)
{
    modelMatrix_ = glm::rotate(base, angle_in_degrees, rotationAxes);
}

void Model::scale(glm::vec3 scale)
{
    modelMatrix_ = glm::scale(modelMatrix_, scale);
}

void Model::scale(glm::mat4 base, glm::vec3 scale)
{
    modelMatrix_ = glm::scale(base, scale);
}

void Model::translate(glm::vec3 position)
{
    modelMatrix_ = glm::translate(modelMatrix_, position);
}

void Model::translate(glm::mat4 base, glm::vec3 position)
{
    modelMatrix_ = glm::translate(base, position);
}

glm::mat4 Model::model_matrix() const
{
    return modelMatrix_;
}

btCollisionShape* Model::collision_shape() const
{
    return collisionShape_; // nullptr
}

void Model::assign_model(glm::mat4 matrix)
{
    modelMatrix_ = matrix;
}
