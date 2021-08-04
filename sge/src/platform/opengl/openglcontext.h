#ifndef _SGE_OPENGLCONTEXT_H
#define _SGE_OPENGLCONTEXT_H

#include "renderingcontext.h"
#include <memory>

#include <SDL2/SDL.h>

namespace SGE {

class OpenGLContext : public RenderingContext {
    private:
        SDL_Window* window_;
        std::unique_ptr<SDL_GLContext> context_;

    public:
        OpenGLContext(SDL_Window* window);
        void swap_buffers() override;
        void delete_context();
};

} // namespace SGE

#endif