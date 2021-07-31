#include "material.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "vector3.h"

#include <assimp/material.h>
#include <glad/glad.h>
#include <memory>
#include <stdexcept>
#include <vector>

namespace SGE {

// TODO: Pass by value and std::move
Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices,
                const Material& material) :
    material_{material}
{
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    vertex_buffer_ = VertexBuffer::create(vertices);
    index_buffer_ = IndexBuffer::create(indices);

    init();
}

void Mesh::init()
{
    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // Vertex texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coordinate));

    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
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

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, index_buffer_->count(), GL_UNSIGNED_INT, nullptr);

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
