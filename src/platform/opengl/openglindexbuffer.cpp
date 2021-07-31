#include "openglindexbuffer.h"
#include "vertex.h"

#include <cstddef>
#include <glad/glad.h>
#include <vector>

namespace SGE {

OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<int>& indices)
    : count_{indices.size()}
{
    glCreateBuffers(1, &buffer_id_);
    bind();

    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            count_ * sizeof(indices[0]),
            indices.data(),
            GL_STATIC_DRAW
            );
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &buffer_id_);
}

void OpenGLIndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
}

std::size_t OpenGLIndexBuffer::count() const
{
    return count_;
}

} // namespace SGE
