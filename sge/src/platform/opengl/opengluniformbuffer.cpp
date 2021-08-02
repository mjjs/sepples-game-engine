#include "opengluniformbuffer.h"

#include <cstdint>
#include <glad/glad.h>

namespace SGE {

    OpenGLUniformBuffer::OpenGLUniformBuffer(const std::uint32_t size,
            const std::uint32_t binding)
    {
        glCreateBuffers(1, &buffer_id_);
        glNamedBufferData(buffer_id_, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, buffer_id_);
    }

    OpenGLUniformBuffer::~OpenGLUniformBuffer()
    {
        glDeleteBuffers(1, &buffer_id_);
    }

    void OpenGLUniformBuffer::set_data(const void* data, const std::uint32_t size,
            const std::uint32_t offset) const
    {
        glNamedBufferSubData(buffer_id_, offset, size, data);
    }

} // namespace SGE
