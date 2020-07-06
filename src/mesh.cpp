#include "mesh.h"
#include "vector3.h"
#include <GL/glew.h>
#include <vector>

Mesh::Mesh(const std::vector<Math::Vector3>& vertices)
{
    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(Math::Vector3),
            vertices.data(),
            GL_STATIC_DRAW
            );
}

void Mesh::draw() const
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}
