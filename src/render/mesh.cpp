#include "bufferlayout.h"
#include "indexbuffer.h"
#include "material.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "vector3.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vector>

#include <assimp/material.h>
#include <glad/glad.h>

namespace SGE {

// TODO: Pass by value and std::move
Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<std::uint32_t>& indices,
                const Material& material) :
    material_{material}
{
    BufferLayout layout{
        { ShaderDataType::VEC3, "position" },
        { ShaderDataType::VEC3, "normal" },
        { ShaderDataType::VEC2, "texture_coordinate" },
    };

    vertex_array_ = VertexArray::create();

    const auto index_buffer = IndexBuffer::create(indices);
    const auto vertex_buffer = VertexBuffer::create(vertices, layout);

    vertex_array_->add_vertex_buffer(vertex_buffer);
    vertex_array_->set_index_buffer(index_buffer);
}

void Mesh::draw(Shader& shader) const
{
    std::uint32_t diffuse_i = 1;
    std::uint32_t specular_i = 1;

    std::vector<Texture> textures = material_.textures();

    for (std::size_t i = 0; i < textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string uniform_name{};
        TextureType texture_type = textures[i].type;

        if (texture_type == TextureType::DIFFUSE) {
            uniform_name = "texture_diffuse" + std::to_string(diffuse_i++) + "_u";
        } else if (texture_type == TextureType::SPECULAR) {
            uniform_name = "texture_specular" + std::to_string(specular_i++) + "_u";
        } else {
            throw std::runtime_error{"Unsupported texture type"};
        }

        shader.add_uniform(uniform_name);
        shader.set_uniform(uniform_name, static_cast<int>(i));

        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    shader.set_material(material_);

    vertex_array_->bind();
    glDrawElements(GL_TRIANGLES, vertex_array_->index_buffer()->count(), GL_UNSIGNED_INT, nullptr);

    for (std::size_t i = 0; i < textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glBindVertexArray(0);
}

const Material& Mesh::material() const
{
    return material_;
}

} // namespace SGE
