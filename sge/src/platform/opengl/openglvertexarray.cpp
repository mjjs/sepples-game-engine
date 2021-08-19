#include "platform/opengl/openglvertexarray.h"

#include "engine/debug/profiler.h"
#include "engine/rendering/buffers/indexbuffer.h"
#include "engine/rendering/buffers/vertexbuffer.h"

#include <cstdint>
#include <glad/glad.h>
#include <memory>
#include <vector>

namespace SGE
{

static GLenum shader_data_type_to_opengl_base_type(ShaderDataType type)
{
    switch (type) {
    case ShaderDataType::NONE:
        return -1;
    case ShaderDataType::FLOAT:
    case ShaderDataType::VEC2:
    case ShaderDataType::VEC3:
    case ShaderDataType::VEC4:
        return GL_FLOAT;
    }
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glCreateVertexArrays(1, &buffer_id_);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &buffer_id_);
}

void OpenGLVertexArray::bind() const
{
    glBindVertexArray(buffer_id_);
}

void OpenGLVertexArray::unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::add_vertex_buffer(
    const std::shared_ptr<VertexBuffer>& vertex_buffer)
{
    SGE_PROFILE_FUNCTION();

    glBindVertexArray(buffer_id_);
    vertex_buffer->bind();

    const auto& layout = vertex_buffer->layout();

    std::size_t i = 0;
    for (const auto& element : layout) {
        glEnableVertexAttribArray(i);

        glVertexAttribPointer(
            i, element.component_count(),
            shader_data_type_to_opengl_base_type(element.type),
            element.normalized ? GL_TRUE : GL_FALSE, layout.stride(),
            (const void*)element.offset);

        ++i;
    }

    vertex_buffers_.push_back(vertex_buffer);
    glBindVertexArray(0);
}

void OpenGLVertexArray::set_index_buffer(
    const std::shared_ptr<IndexBuffer>& index_buffer)
{
    glBindVertexArray(buffer_id_);
    index_buffer->bind();

    index_buffer_ = index_buffer;
    glBindVertexArray(0);
}

const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::
    vertex_buffers()
{
    return vertex_buffers_;
}

const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::index_buffer()
{
    return index_buffer_;
}

} // namespace SGE
