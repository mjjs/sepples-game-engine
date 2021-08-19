#ifndef _SGE_OPENGL_VERTEXBUFFER_H
#define _SGE_OPENGL_VERTEXBUFFER_H

#include "engine/rendering/buffers/bufferlayout.h"
#include "engine/rendering/buffers/vertexbuffer.h"
#include "engine/rendering/vertex.h"

#include <cstdint>
#include <vector>

namespace SGE
{

class OpenGLVertexBuffer : public VertexBuffer
{
  private:
    std::uint32_t buffer_id_ = 0;
    BufferLayout layout_;

  public:
    OpenGLVertexBuffer(const std::vector<Vertex>& vertices,
                       BufferLayout layout);
    OpenGLVertexBuffer(std::uint32_t size);

    ~OpenGLVertexBuffer();

    OpenGLVertexBuffer(const OpenGLVertexBuffer&)  = delete;
    OpenGLVertexBuffer(const OpenGLVertexBuffer&&) = delete;
    OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&) = delete;
    OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&&) = delete;

    void bind() const override;
    const BufferLayout& layout() const override;
    void set_layout(const BufferLayout& layout) override;
    void set_data(const void* data, std::uint32_t size) override;
};

} // namespace SGE

#endif
