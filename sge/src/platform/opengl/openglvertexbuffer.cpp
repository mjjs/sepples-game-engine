#include "platform/opengl/openglvertexbuffer.h"

#include "engine/debug/profiler.h"
#include "engine/rendering/buffers/bufferlayout.h"
#include "engine/rendering/vertex.h"

#include <cstdint>
#include <glad/glad.h>
#include <vector>

namespace SGE
{

OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<Vertex>& vertices,
                                       const BufferLayout layout)
    : layout_{layout}
{
    SGE_PROFILE_FUNCTION();

    glCreateBuffers(1, &buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]),
                 vertices.data(), GL_STATIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const std::uint32_t size)
{
    SGE_PROFILE_FUNCTION();

    glCreateBuffers(1, &buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);

    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &buffer_id_);
}

void OpenGLVertexBuffer::bind() const
{
    SGE_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
}

const BufferLayout& OpenGLVertexBuffer::layout() const
{
    return layout_;
}

void OpenGLVertexBuffer::set_layout(const BufferLayout& layout)
{
    layout_ = layout;
}

void OpenGLVertexBuffer::set_data(const void* data, const std::uint32_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

} // namespace SGE
