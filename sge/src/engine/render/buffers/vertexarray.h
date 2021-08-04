#ifndef _SGE_VERTEXARRAY_H
#define _SGE_VERTEXARRAY_H

#include "indexbuffer.h"
#include "vertexbuffer.h"

#include <memory>
#include <vector>

namespace SGE
{

class VertexArray
{
  public:
    VertexArray()          = default;
    virtual ~VertexArray() = default;

    VertexArray(const VertexArray&)  = delete;
    VertexArray(const VertexArray&&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&&) = delete;

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual void
    add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) = 0;
    virtual void
    set_index_buffer(const std::shared_ptr<IndexBuffer>& index_buffer) = 0;

    virtual const std::vector<std::shared_ptr<VertexBuffer>>&
    vertex_buffers()                                           = 0;
    virtual const std::shared_ptr<IndexBuffer>& index_buffer() = 0;

    static std::shared_ptr<VertexArray> create();
};

} // namespace SGE

#endif
