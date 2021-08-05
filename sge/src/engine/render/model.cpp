#include "model.h"

#include "material.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "texture2d.h"
#include "vector2.h"
#include "vector3.h"
#include "vertex.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace SGE
{

constexpr char const* COLOUR_AMBIENT  = "AMBIENT";
constexpr char const* COLOUR_DIFFUSE  = "DIFFUSE";
constexpr char const* COLOUR_SPECULAR = "SPECULAR";

static Vector3 get_colour(const aiMaterial& material, const std::string& type);
static float get_shininess(const aiMaterial& material);

Model::Model(const std::string& path)
{
    load_model(path);
}

void Model::load_model(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        path, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate);

    if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        scene->mRootNode == nullptr) {
        throw std::runtime_error("Error loading model: " +
                                 std::string(importer.GetErrorString()));
    }

    directory_ = path.substr(0, path.find_last_of('/'));

    process_node(scene->mRootNode, scene);
}

void Model::process_node(aiNode* node, const aiScene* scene)
{
    for (std::size_t i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh  = scene->mMeshes[node->mMeshes[i]];
        auto mesh_ptr = std::make_shared<Mesh>(process_mesh(mesh, scene));
        meshes_.push_back(mesh_ptr);
    }

    for (std::size_t i = 0; i < node->mNumChildren; ++i) {
        process_node(node->mChildren[i], scene);
    }
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<std::uint32_t> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    for (std::size_t i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;
        vertex.position = Vector3{mesh->mVertices[i].x, mesh->mVertices[i].y,
                                  mesh->mVertices[i].z};

        if (mesh->HasNormals()) {
            vertex.normal = Vector3{mesh->mNormals[i].x, mesh->mNormals[i].y,
                                    mesh->mNormals[i].z};
        }

        if (mesh->HasTextureCoords(0)) {
            vertex.texture_coordinate = Vector2{mesh->mTextureCoords[0][i].x,
                                                mesh->mTextureCoords[0][i].y};
        } else {
            vertex.texture_coordinate = Vector2{0.0F, 0.0F};
        }

        vertices.push_back(vertex);
    }

    for (std::size_t i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];

        for (std::size_t j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* assimp_material = scene->mMaterials[mesh->mMaterialIndex];
    Material material;

    if (assimp_material != nullptr) {
        std::vector<std::shared_ptr<Texture>> diffuse_maps =
            load_material_textures(assimp_material, aiTextureType_DIFFUSE);

        textures.insert(textures.end(), diffuse_maps.begin(),
                        diffuse_maps.end());

        std::vector<std::shared_ptr<Texture>> specular_maps =
            load_material_textures(assimp_material, aiTextureType_SPECULAR);

        textures.insert(textures.end(), specular_maps.begin(),
                        specular_maps.end());

        material.set_ambient(get_colour(*assimp_material, COLOUR_AMBIENT));
        material.set_diffuse(get_colour(*assimp_material, COLOUR_DIFFUSE));
        material.set_specular(get_colour(*assimp_material, COLOUR_SPECULAR));
        material.set_shininess(get_shininess(*assimp_material));

        material.set_textures(textures);
    }

    return Mesh{vertices, indices, material};
}

std::vector<std::shared_ptr<Texture>> Model::load_material_textures(
    aiMaterial* material, const aiTextureType texture_type)
{
    std::vector<std::shared_ptr<Texture>> textures;

    for (std::size_t i = 0; i < material->GetTextureCount(texture_type); ++i) {
        aiString path;
        material->GetTexture(texture_type, i, &path);
        std::string filename{path.C_Str()};

        auto full_path = directory_ + "/" + filename;

        if (loaded_textures_.contains(full_path)) {
            textures.push_back(loaded_textures_[full_path]);
        } else {
            auto tt = texture_type == aiTextureType_DIFFUSE
                          ? Texture::Type::DIFFUSE
                          : Texture::Type::SPECULAR;

            auto texture = Texture2D::create(full_path, tt);
            textures.push_back(texture);
            loaded_textures_[full_path] = texture;
        }
    }

    return textures;
}

void Model::draw(Shader& shader) const
{
    for (const auto& mesh : meshes_) {
        mesh->draw(shader);
    }
}

Vector3 get_colour(const aiMaterial& material, const std::string& type)
{
    aiColor3D colour{};

    if (type == COLOUR_AMBIENT) {
        material.Get(AI_MATKEY_COLOR_AMBIENT, colour);
    } else if (type == COLOUR_DIFFUSE) {
        material.Get(AI_MATKEY_COLOR_DIFFUSE, colour);
    } else if (type == COLOUR_SPECULAR) {
        material.Get(AI_MATKEY_COLOR_SPECULAR, colour);
    }

    return Vector3{colour.r, colour.g, colour.b};
}

float get_shininess(const aiMaterial& material)
{
    float shininess = 1.0;
    material.Get(AI_MATKEY_SHININESS, shininess);
    return shininess;
}

const std::vector<std::shared_ptr<Mesh>>& Model::meshes() const
{
    return meshes_;
}

} // namespace SGE
