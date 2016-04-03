#include "Model.h"
using namespace std;

Model::Model(const string &path)
{
    collisionMesh_ = new btTriangleMesh();

    load_model(path.c_str());

    modelMatrix_ = glm::mat4(1.0f);
    collisionShape_ = new btBvhTriangleMeshShape(collisionMesh_, true);
}

Model::~Model()
{
    free();
}

void Model::free()
{
    // TODO: change these to unique_ptrs
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

void Model::draw(const ShaderProgram* shaderProgram)
{
    for (GLuint i = 0; i < meshes_.size(); i++)
    {
        meshes_[i].draw(shaderProgram);
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
        meshes_.push_back(process_mesh(mesh, scene));
        meshes_.back().setup_mesh();
    }

    // Process all child nodes
    for (GLuint i = 0; i < node->mNumChildren; i++)
    {
        process_node(node->mChildren[i], scene);
    }
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene) const
{
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    btVector3 triArray[3];

    // Cycle through the faces in the mesh (each is a triangle)
    for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];

        // Use the indices of the face to grab vertex data
        for (GLuint j = 0; j < face.mNumIndices; j++)
        {
            // Build the triangle for the collision mesh
            aiVector3D position = mesh->mVertices[face.mIndices[j]];
            triArray[j] = btVector3(position.x, position.y, position.z);

            // Store the index
            indices.push_back(face.mIndices[j]);
        }

        collisionMesh_->addTriangle(triArray[0], triArray[1], triArray[2]);
    }

    // Cycle through the vertices and store their data
    for (GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex tempVertex;

        auto vertex = make_unique<const aiVector3D>(mesh->mVertices[i]);
        tempVertex.position.x = vertex->x;
        tempVertex.position.y = vertex->y;
        tempVertex.position.z = vertex->z;

        auto normal = make_unique<const aiVector3D>(mesh->mNormals[i]);
        tempVertex.normal.x = normal->x;
        tempVertex.normal.y = normal->y;
        tempVertex.normal.z = normal->z;

        // Texture Coordinates
        if (mesh->HasTextureCoords(0))
        {
            tempVertex.tex_coords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }
        else
        {
            tempVertex.tex_coords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(tempVertex);
    }

    // Process materials
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        vector<Texture> diffuseMaps = load_textures(material, aiTextureType_DIFFUSE);
        vector<Texture> specularMaps = load_textures(material, aiTextureType_SPECULAR);

        textures.reserve(diffuseMaps.size() + specularMaps.size());
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::load_textures(aiMaterial* material, aiTextureType type)
{
    // TODO: optimize this to use a texture cache
    vector<Texture> textures;
    for (size_t i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString filename;
        material->GetTexture(type, i, &filename);
        Texture texture(type);
        texture.load(filename.C_Str());
        textures.push_back(texture);
    }
    return textures;
}

// Transformations
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
    return collisionShape_;
}

void Model::assign_model(glm::mat4 matrix)
{
    modelMatrix_ = matrix;
}
