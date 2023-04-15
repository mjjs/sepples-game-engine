#ifndef _SGE_OPENGLCONTEXT_H
#define _SGE_OPENGLCONTEXT_H

#include "engine/rendering/renderingcontext.h"

#include <SDL.h>
#include <memory>

namespace SGE
{

class OpenGLContext : public RenderingContext
{
  private:
    SDL_Window* window_;
    std::unique_ptr<SDL_GLContext> context_;

  public:
    OpenGLContext(SDL_Window* window);
    void swap_buffers() override;

    void* raw_context() const override
    {
        return context_.get();
    }

    void delete_context();
};

} // namespace SGE

#endif
