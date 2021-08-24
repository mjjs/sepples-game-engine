#ifndef _SGE_OPENGL_FRAMEBUFFER_H
#define _SGE_OPENGL_FRAMEBUFFER_H

#include "engine/rendering/framebuffer.h"

#include <cstdint>
#include <vector>

namespace SGE
{

class OpenGLFramebuffer : public Framebuffer
{
  private:
    std::uint32_t buffer_id_            = 0;
    std::uint32_t colour_attachment_id_ = 0;
    std::uint32_t depth_attachment_id_  = 0;

    FramebufferConfig config_;

  public:
    OpenGLFramebuffer(const FramebufferConfig& config);
    ~OpenGLFramebuffer();

    OpenGLFramebuffer(const OpenGLFramebuffer&)  = delete;
    OpenGLFramebuffer(const OpenGLFramebuffer&&) = delete;
    OpenGLFramebuffer& operator=(const OpenGLFramebuffer&) = delete;
    OpenGLFramebuffer& operator=(const OpenGLFramebuffer&&) = delete;

    void bind() const override;
    void unbind() const override;

    std::uint32_t colour_attachment_buffer_id() const override
    {
        return colour_attachment_id_;
    }
};

} // namespace SGE

#endif
