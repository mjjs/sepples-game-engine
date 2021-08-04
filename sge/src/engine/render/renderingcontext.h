#ifndef _SGE_RENDERINGCONTEXT_H
#define _SGE_RENDERINGCONTEXT_H

namespace SGE
{

class RenderingContext
{
  public:
    RenderingContext()                         = default;
    RenderingContext(const RenderingContext&)  = delete;
    RenderingContext(const RenderingContext&&) = delete;
    RenderingContext& operator=(const RenderingContext&) = delete;
    RenderingContext& operator=(const RenderingContext&&) = delete;
    virtual ~RenderingContext()                           = default;

    virtual void swap_buffers() = 0;
};

} // namespace SGE

#endif
