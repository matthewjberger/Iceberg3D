#include "Model.h"
using namespace std;

Model::Model(string path)
{
    textureLoaded = false;
    LoadModel(path.c_str());
}

void Model::Free()
{
    for(GLuint i = 0; i < meshes.size(); i++)
    {
        meshes[i].Free();
    }
}

void Model::Draw()
{
    for(GLuint i = 0; i < meshes.size(); i++)
    {
        texture.Bind(0);
        meshes[i].Draw();
    }
}

void Model::LoadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR: Assimp - " << importer.GetErrorString() << endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // Process all meshes in the node
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh));
        meshes.back().SetupMesh();
    }

    // Process all child nodes
    for(GLuint i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh)
{
    vector<Vertex> vertices;
    vector<GLuint> indices;

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

    for(unsigned int i = 0; i < indices.size(); i++)
    {
        const aiVector3D* temp = &(mesh->mVertices[indices[i]]);
        Vertex v;
        v.Position.x = temp->x;
        v.Position.y = temp->y;
        v.Position.z = temp->z;

        // Texture Coordinates
        if(mesh->HasTextureCoords(0))
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

void Model::LoadTexture(string image, bool genMipMaps)
{
    texture.Load(image, genMipMaps);
}

