#ifndef _SGE_OPENGL_UNIFORMBUFFER_H
#define _SGE_OPENGL_UNIFORMBUFFER_H

#include "uniformbuffer.h"

#include <cstdint>

namespace SGE {

class OpenGLUniformBuffer : public UniformBuffer {
    private:
        std::uint32_t buffer_id_ = 0;

    public:
        OpenGLUniformBuffer(std::uint32_t size, std::uint32_t binding);
        ~OpenGLUniformBuffer();

        OpenGLUniformBuffer(const OpenGLUniformBuffer&) = delete;
        OpenGLUniformBuffer(const OpenGLUniformBuffer&&) = delete;
        OpenGLUniformBuffer& operator=(const OpenGLUniformBuffer&) = delete;
        OpenGLUniformBuffer& operator=(const OpenGLUniformBuffer&&) = delete;

        void set_data(
                const void* data,
                std::uint32_t size,
                std::uint32_t offset = 0
                ) const override;
};

} // SGE

#endif
