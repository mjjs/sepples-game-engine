#ifndef _SGE_OPENGL_INDEXBUFFER_H
#define _SGE_OPENGL_INDEXBUFFER_H

#include "engine/rendering/buffers/indexbuffer.h"
#include "engine/rendering/vertex.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace SGE
{

class OpenGLIndexBuffer : public IndexBuffer
{
  private:
    std::uint32_t buffer_id_ = 0;
    std::size_t count_       = 0;

  public:
    OpenGLIndexBuffer(const std::vector<std::uint32_t>& indices);
    ~OpenGLIndexBuffer();

    OpenGLIndexBuffer(const OpenGLIndexBuffer&)  = delete;
    OpenGLIndexBuffer(const OpenGLIndexBuffer&&) = delete;
    OpenGLIndexBuffer& operator=(const OpenGLIndexBuffer&) = delete;
    OpenGLIndexBuffer& operator=(const OpenGLIndexBuffer&&) = delete;

    void bind() const override;
    std::size_t count() const override;
};

} // namespace SGE

#endif
