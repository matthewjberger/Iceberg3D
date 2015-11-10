#include "Model.h"
using namespace std;

Model::Model(string path, string texturePath, bool genMipMaps)
{
    collisionMesh = new btTriangleMesh();

    textureLoaded = false;
    LoadModel(path.c_str());

    if(texturePath != "")
    {
        LoadTexture(texturePath, genMipMaps);
    }

    modelMatrix = glm::mat4(1.0f);
    collisionShape = new btBvhTriangleMeshShape(collisionMesh, true);
}

void Model::Free()
{
    for(GLuint i = 0; i < meshes.size(); i++)
    {
        meshes[i].Free();
    }

    if(collisionMesh != NULL)
    {
        delete collisionMesh;
        collisionMesh = NULL;
    }

    if(collisionShape != NULL)
    {
        delete collisionShape;
        collisionShape = NULL;
    }
}

void Model::Draw()
{
    for(GLuint i = 0; i < meshes.size(); i++)
    {
        if(textureLoaded)
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
    btVector3 triArray[3];

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        for(int j = 0; j < face.mNumIndices; j++)
        {
            aiVector3D position = mesh->mVertices[face.mIndices[j]];
            triArray[j] = btVector3(position.x, position.y, position.z);
            indices.push_back(face.mIndices[j]);
        }
        collisionMesh->addTriangle(triArray[0], triArray[1], triArray[2]);
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
    textureLoaded = true;
}

void Model::Rotate(float angle_in_degrees, glm::vec3 rotationAxes)
{
    modelMatrix = glm::rotate(modelMatrix, angle_in_degrees, rotationAxes);
}

void Model::Rotate(glm::mat4 base, float angle_in_degrees, glm::vec3 rotationAxes)
{
    modelMatrix = glm::rotate(base, angle_in_degrees, rotationAxes);
}

void Model::Scale(glm::vec3 scale)
{
    modelMatrix = glm::scale(modelMatrix, scale);
}

void Model::Scale(glm::mat4 base, glm::vec3 scale)
{
    modelMatrix = glm::scale(base, scale);
}

void Model::Translate(glm::vec3 position)
{
    modelMatrix = glm::translate(modelMatrix, position);
}

void Model::Translate(glm::mat4 base, glm::vec3 position)
{
    modelMatrix = glm::translate(base, position);
}

glm::mat4 Model::GetModelMatrix()
{
    return modelMatrix;
}

btCollisionShape* Model::GetCollisionShape()
{
    return collisionShape; // null
}

void Model::SetModelMatrix(glm::mat4 matrix)
{
    modelMatrix = matrix;
}

