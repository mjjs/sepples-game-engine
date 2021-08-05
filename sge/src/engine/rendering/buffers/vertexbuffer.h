#ifndef _SGE_VERTEXBUFFER_H
#define _SGE_VERTEXBUFFER_H

#include "bufferlayout.h"
#include "vertex.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace SGE
{

class VertexBuffer
{
  public:
    VertexBuffer()                             = default;
    virtual ~VertexBuffer()                    = default;
    virtual void bind() const                  = 0;
    virtual const BufferLayout& layout() const = 0;

    VertexBuffer(const VertexBuffer&)  = delete;
    VertexBuffer(const VertexBuffer&&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&&) = delete;

    static std::shared_ptr<VertexBuffer>
    create(const std::vector<Vertex>& vertices, BufferLayout layout);
};

} // namespace SGE

#endif
