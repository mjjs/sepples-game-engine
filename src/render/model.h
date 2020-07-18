#ifndef _SGE_MODEL_H
#define _SGE_MODEL_H
#include "mesh.h"
#include "shader.h"
#include "vector3.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <string>
#include <vector>

class Model {
    private:
        std::vector<Mesh> meshes_;
        std::string directory_;
        std::vector<Texture> loaded_textures_;

        void load_model(const std::string& path);
        void process_node(aiNode* node, const aiScene* scene);
        Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> load_material_textures(aiMaterial* material,
                aiTextureType type, const std::string& type_name);

    public:
        explicit Model(const std::string& path);
        void draw(Shader& shader) const;
};

Math::Vector3 get_colour(const aiMaterial& material, const std::string& colour_key);

#endif
