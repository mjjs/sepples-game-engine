#include "openglvertexbuffer.h"
#include "vertex.h"

#include <glad/glad.h>
#include <vector>

namespace SGE {

OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<Vertex>& vertices)
{
    glCreateBuffers(1, &buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
    glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(vertices[0]),
            vertices.data(),
            GL_STATIC_DRAW
            );
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &buffer_id_);
}

void OpenGLVertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
}

} // namespace SGE
