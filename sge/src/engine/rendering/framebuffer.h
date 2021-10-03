#ifndef _SGE_FRAMEBUFFER_H
#define _SGE_FRAMEBUFFER_H

#include <memory>

namespace SGE
{

struct FramebufferConfig {
    std::uint32_t width   = 0;
    std::uint32_t height  = 0;
    std::uint32_t samples = 1;

    bool part_of_swap_chain = false;
};

class Framebuffer
{
  public:
    Framebuffer()          = default;
    virtual ~Framebuffer() = default;

    Framebuffer(const Framebuffer&)  = delete;
    Framebuffer(const Framebuffer&&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;
    Framebuffer& operator=(const Framebuffer&&) = delete;

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual std::uint32_t colour_attachment_buffer_id() const      = 0;
    virtual void resize(std::uint32_t width, std::uint32_t height) = 0;

    static std::shared_ptr<Framebuffer> create(const FramebufferConfig& config);
};

} // namespace SGE

#endif
