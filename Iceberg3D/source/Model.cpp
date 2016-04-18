#include "Model.h"
using namespace std;
#include <stb_image.h>

Model::Model(const string &path)
{
    load_model(path.c_str());

    transformManager_ = make_shared<TransformManager>();
}

Model::~Model()
{
}

void Model::draw(const ShaderProgram* shaderProgram, const Camera* camera)
{
    for (GLuint i = 0; i < meshes_.size(); i++)
    {
       meshes_[i].draw(shaderProgram);
    }
}

bool Model::load_model(const string &path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        string errorMessage = "Assimp - ";
        errorMessage += importer.GetErrorString();
        Game::handle_error(errorMessage.c_str());
        return false;
    }

    directory_ = path.substr(0, path.find_last_of('/'));
    process_node(scene->mRootNode, scene);

    return true;
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

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Tex> textures;

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

        vector<Tex> diffuseMaps = load_textures(material, aiTextureType_DIFFUSE);
        vector<Tex> specularMaps = load_textures(material, aiTextureType_SPECULAR);

        textures.reserve(diffuseMaps.size() + specularMaps.size());
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Tex> Model::load_textures(aiMaterial* material, aiTextureType type)
{
    // TODO: Improve texture cache lookup time with a hash table
    vector<Tex> textures;
    for (size_t i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString filename;
        material->GetTexture(type, i, &filename);
        string filepath = directory_ + "/" + filename.C_Str();
 
        bool found = false;
        for(auto t : textureCache_)
        {
            if(t.path.C_Str() == filepath)
            {
                textures.push_back(t);
                found = true;
                break;
            }

        }

        if(!found)
        {
            Tex texture;
            texture.type = type;
            texture.path = filepath;
            texture.id = load_texture(filepath);
            textureCache_.push_back(texture);
            textures.push_back(texture);
        }
    }
    return textures;
}

TransformManager* Model::transform_manager() const
{
    return transformManager_.get();
}

int Model::load_texture(const string &path) const
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!image)
    {
        string errorMessage = "Error: Couldn't load image: " + path;
        Game::handle_error(errorMessage);
        return false;
    }

    GLenum pixelFormat = GL_RGB;
    switch (channels)
    {
        case 1: pixelFormat = GL_ALPHA;     break;
        case 2: pixelFormat = GL_LUMINANCE; break;
        case 3: pixelFormat = GL_RGB;       break;
        case 4: pixelFormat = GL_RGBA;      break;
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Get rid of the temporary surface
    stbi_image_free(image);

    return textureID;
}