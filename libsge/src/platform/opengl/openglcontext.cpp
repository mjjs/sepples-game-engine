#include "openglcontext.h"

#include <glad/glad.h>
#include <memory>
#include <SDL2/SDL.h>

namespace SGE {

OpenGLContext::OpenGLContext(SDL_Window* window)
    : window_{window}, context_{std::make_unique<SDL_GLContext>(SDL_GL_CreateContext(window))}
{
    int status = gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress);
    if (status == 0) {
        throw std::runtime_error("Could not init GLEW");
    }

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
}

void OpenGLContext::swap_buffers()
{
    SDL_GL_SwapWindow(window_);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLContext::delete_context()
{
    SDL_GL_DeleteContext(*context_);
}

} // namespace SGE
