#include "mesh.h"

#include "bufferlayout.h"
#include "indexbuffer.h"
#include "log.h"
#include "material.h"
#include "shader.h"
#include "texture.h"
#include "vector3.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

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

    std::vector<std::shared_ptr<Texture>> textures = material_.textures();

    for (std::size_t i = 0; i < textures.size(); ++i) {
        auto texture = textures[i];

        switch (texture->type()) {
        case Texture::Type::DIFFUSE:
            shader.set_uniform("texture_diffuse_u", static_cast<int>(i));
            break;
        case Texture::Type::SPECULAR:
            shader.set_uniform("texture_specular_u", static_cast<int>(i));
            break;
        case Texture::Type::NORMAL:
            LOG_INFO("Unsupported texture type: NORMAL");
        }

        texture->bind(i);
    }

    shader.set_material(material_);

    vertex_array_->bind();
    glDrawElements(GL_TRIANGLES, vertex_array_->index_buffer()->count(),
                   GL_UNSIGNED_INT, nullptr);

    for (const auto& texture : textures) {
        texture->unbind();
    }

    vertex_array_->unbind();
}

const Material& Mesh::material() const
{
    return material_;
}

} // namespace SGE
