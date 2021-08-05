#include "engine/rendering/mesh.h"

#include "engine/rendering/buffers/bufferlayout.h"
#include "engine/rendering/buffers/indexbuffer.h"
#include "engine/core/log.h"
#include "engine/rendering/material.h"
#include "engine/rendering/shaders/shader.h"
#include "engine/rendering/texture.h"
#include "engine/math/vector3.h"
#include "engine/rendering/buffers/vertexarray.h"
#include "engine/rendering/buffers/vertexbuffer.h"

#include <assimp/material.h>
#include <cstdint>
#include <glad/glad.h>
#include <memory>
#include <stdexcept>
#include <vector>

namespace SGE
{

// TODO: Pass by value and std::move
Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<std::uint32_t>& indices, const Material& material)
    : material_{material}
{
    BufferLayout layout{
        {ShaderDataType::VEC3, "position"},
        {ShaderDataType::VEC3, "normal"},
        {ShaderDataType::VEC2, "texture_coordinate"},
    };

    vertex_array_ = VertexArray::create();

    const auto index_buffer  = IndexBuffer::create(indices);
    const auto vertex_buffer = VertexBuffer::create(vertices, layout);

    vertex_array_->add_vertex_buffer(vertex_buffer);
    vertex_array_->set_index_buffer(index_buffer);
}

void Mesh::draw(Shader& shader) const
{
    shader.bind();

    const auto diffuse_map  = material_.diffuse_texture();
    const auto specular_map = material_.specular_texture();
    const auto normal_map   = material_.normal_texture();

    if (diffuse_map) {
        diffuse_map->bind(0);
        shader.set_uniform("material_u.texture_diffuse", 0);
    }

    if (specular_map) {
        specular_map->bind(1);
        shader.set_uniform("material_u.texture_specular", 1);
    }

    if (normal_map) {
        normal_map->bind(2);
        shader.set_uniform("material_u.texture_normal", 2);
    }

    shader.set_uniform("material_u.shininess", material_.shininess());

    vertex_array_->bind();
    glDrawElements(GL_TRIANGLES, vertex_array_->index_buffer()->count(),
                   GL_UNSIGNED_INT, nullptr);

    if (diffuse_map) {
        diffuse_map->unbind();
    }

    if (specular_map) {
        specular_map->unbind();
    }

    if (normal_map) {
        normal_map->unbind();
    }

    vertex_array_->unbind();
}

const Material& Mesh::material() const
{
    return material_;
}

} // namespace SGE
