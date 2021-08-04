#ifndef _SGE_OPENGL_VERTEXARRAY_H
#define _SGE_OPENGL_VERTEXARRAY_H

#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace SGE
{

class OpenGLVertexArray : public VertexArray
{
  private:
    std::uint32_t buffer_id_ = 0;
    std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers_;
    std::shared_ptr<IndexBuffer> index_buffer_;

  public:
    OpenGLVertexArray();
    ~OpenGLVertexArray();

    OpenGLVertexArray(const OpenGLVertexArray&)  = delete;
    OpenGLVertexArray(const OpenGLVertexArray&&) = delete;
    OpenGLVertexArray& operator=(const OpenGLVertexArray&) = delete;
    OpenGLVertexArray& operator=(const OpenGLVertexArray&&) = delete;

    void bind() const override;
    void unbind() const override;

    void add_vertex_buffer(
        const std::shared_ptr<VertexBuffer>& vertex_buffer) override;
    void
    set_index_buffer(const std::shared_ptr<IndexBuffer>& index_buffer) override;

    const std::vector<std::shared_ptr<VertexBuffer>>& vertex_buffers() override;
    const std::shared_ptr<IndexBuffer>& index_buffer() override;
};

} // namespace SGE

#endif
