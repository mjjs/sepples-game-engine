#ifndef _SGE_VERTEXBUFFER_H
#define _SGE_VERTEXBUFFER_H

#include "engine/rendering/buffers/bufferlayout.h"
#include "engine/rendering/vertex.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace SGE
{

class VertexBuffer
{
  public:
    VertexBuffer()          = default;
    virtual ~VertexBuffer() = default;

    virtual void bind() const                                   = 0;
    virtual const BufferLayout& layout() const                  = 0;
    virtual void set_layout(const BufferLayout& layout)         = 0;
    virtual void set_data(const void* data, std::uint32_t size) = 0;

    VertexBuffer(const VertexBuffer&)  = delete;
    VertexBuffer(const VertexBuffer&&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&&) = delete;

    static std::shared_ptr<VertexBuffer> create(
        const std::vector<Vertex>& vertices, BufferLayout layout);
    static std::shared_ptr<VertexBuffer> create(std::uint32_t size);
};

} // namespace SGE

#endif
