#include "mesh.h"
#include "shader.h"
#include "vector3.h"
#include <GL/glew.h>
#include <vector>

// TODO: Pass by value and std::move
Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices,
                const std::vector<Texture>& textures) :
    vertices_{vertices},
    indices_{indices},
    textures_{textures}
{
    init();
}

void Mesh::init()
{
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ibo_);
    glGenVertexArrays(1, &vao_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(
            GL_ARRAY_BUFFER,
            vertices_.size() * sizeof(Vertex),
            vertices_.data(),
            GL_STATIC_DRAW
            );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            indices_.size() * sizeof(int),
            indices_.data(),
            GL_STATIC_DRAW
            );

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

    for (std::size_t i = 0; i < textures_.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name = textures_[i].type;

        if (name == "texture_diffuse") {
            number = std::to_string(diffuse_i++);
        } else if (name == "texture_specular") {
            number = std::to_string(specular_i++);
        }

        const std::string uniform_name{name + number};

        shader.add_uniform(uniform_name);
        shader.set_uniform(uniform_name, static_cast<int>(i));
        glBindTexture(GL_TEXTURE_2D, textures_[i].id);
    }

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
