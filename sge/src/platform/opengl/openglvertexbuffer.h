#ifndef _SGE_OPENGL_VERTEXBUFFER_H
#define _SGE_OPENGL_VERTEXBUFFER_H

#include "bufferlayout.h"
#include "vertexbuffer.h"
#include "vertex.h"

#include <cstdint>
#include <vector>

namespace SGE {

class OpenGLVertexBuffer : public VertexBuffer {
    private:
        std::uint32_t buffer_id_ = 0;
        BufferLayout layout_;

    public:
        OpenGLVertexBuffer(const std::vector<Vertex>& vertices, BufferLayout layout);
        ~OpenGLVertexBuffer();

        OpenGLVertexBuffer(const OpenGLVertexBuffer&) = delete;
        OpenGLVertexBuffer(const OpenGLVertexBuffer&&) = delete;
        OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&) = delete;
        OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&&) = delete;

        void bind() const override;
        const BufferLayout& layout() const override;

};

} // SGE

#endif
