#include "Model.h"
using namespace std;

Model::Model(const string &path)
{
    load_model(path.c_str());

    transformManager_ = make_shared<TransformManager>();
}

Model::~Model()
{
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

    // Get the indices of the corresponding vertices of each face 
    for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        for (GLuint j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
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

std::vector<Texture> Model::load_textures(aiMaterial* material, aiTextureType type) const
{
    // TODO: optimize this to use a texture cache
    vector<Texture> textures;
    for (size_t i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString filename;
        material->GetTexture(type, i, &filename);
        Texture texture(type);
        string filepath = directory_ + "/" + filename.C_Str();
        texture.load(filename.C_Str());
        textures.push_back(texture);
    }
    return textures;
}

TransformManager* Model::transform_manager() const
{
    return transformManager_.get();
}
