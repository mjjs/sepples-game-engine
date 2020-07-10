#include "mesh.h"
#include "vector3.h"
#include <GL/glew.h>
#include <vector>

Mesh::Mesh()
{
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ibo_);
}

Mesh::Mesh(const std::vector<Math::Vector3>& vertices, const std::vector<int>& indices)
{
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ibo_);

    set_vertices(vertices, indices);
}

void Mesh::set_vertices(const std::vector<Math::Vector3>& vertices, const std::vector<int>& indices)
{
    size_ = indices.size();

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(Math::Vector3),
            vertices.data(),
            GL_STATIC_DRAW
            );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            size_ * sizeof(int),
            indices.data(),
            GL_STATIC_DRAW
            );
}

void Mesh::draw() const
{
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glDrawElements(GL_TRIANGLES, size_, GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(0);
}
