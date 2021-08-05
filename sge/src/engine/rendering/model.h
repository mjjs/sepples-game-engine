#ifndef _SGE_MODEL_H
#define _SGE_MODEL_H

#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "vector3.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace SGE
{

class Model
{
  private:
    std::vector<std::shared_ptr<Mesh>> meshes_;
    std::string directory_;
    std::unordered_map<std::string, std::shared_ptr<Texture>> loaded_textures_;

    void load_model(const std::string& path);
    void process_node(aiNode* node, const aiScene* scene);
    Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
    std::shared_ptr<Texture> load_material_texture(aiMaterial* material,
                                                   aiTextureType texture_type);

  public:
    explicit Model(const std::string& path);
    void draw(Shader& shader) const;

    const std::vector<std::shared_ptr<Mesh>>& meshes() const;
};

} // namespace SGE

#endif
