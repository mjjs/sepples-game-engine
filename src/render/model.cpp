#include "mesh.h"
#include "model.h"
#include "resourceloader.h"
#include "shader.h"
#include "texture.h"
#include "vector2.h"
#include "vector3.h"
#include "vertex.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

Model::Model(const std::string& path)
{
    load_model(path);
}

void Model::load_model(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,
            aiProcess_Triangulate | aiProcess_FlipUVs);

    if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
            scene->mRootNode == nullptr) {
        throw std::runtime_error("Error loading model: " + std::string(importer.GetErrorString()));
    }

    directory_ = path.substr(0, path.find_last_of('/'));

    process_node(scene->mRootNode, scene);
}

void Model::process_node(aiNode* node, const aiScene* scene)
{
    for (std::size_t i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes_.push_back(process_mesh(mesh, scene));
    }

    for (std::size_t i = 0; i < node->mNumChildren; ++i) {
        process_node(node->mChildren[i], scene);
    }
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    std::vector<Texture> textures;

    for (std::size_t i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;
        vertex.position = Math::Vector3{
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };

        vertex.normal = Math::Vector3{
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
        };

        if (mesh->mTextureCoords[0]) {
            vertex.texture_coordinate = Math::Vector2{
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y,
            };
        }

        vertices.push_back(vertex);
    }

    for (std::size_t i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];

        for (std::size_t j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuse_maps = load_material_textures(material,
            aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

    std::vector<Texture> specular_maps = load_material_textures(material,
            aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

    return Mesh{vertices, indices, textures};
}

std::vector<Texture> Model::load_material_textures(aiMaterial* material, aiTextureType type,
        const std::string& type_name)
{
    std::vector<Texture> textures;

    for (std::size_t i = 0; i < material->GetTextureCount(type); ++i) {
        aiString tmp_path;
        material->GetTexture(type, i, &tmp_path);
        std::string path{tmp_path.C_Str()};

        bool already_loaded = false;

        for (const Texture& texture : loaded_textures_) {
            if (path == texture.path) {
                textures.push_back(texture);
                already_loaded = true;
                break;
            }
        }

        if (!already_loaded) {
            Texture texture{
                load_texture(path, directory_),
                    type_name,
                    path
            };

            textures.push_back(texture);
            loaded_textures_.push_back(texture);
        }
    }

    return textures;
}

void Model::draw(Shader& shader) const
{
    for (const Mesh& mesh : meshes_) {
        mesh.draw(shader);
    }
}