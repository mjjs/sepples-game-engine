#include "platform/opengl/openglcontext.h"

#include "engine/debug/profiler.h"
#include "engine/rendering/renderer.h"

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <memory>

namespace SGE
{

OpenGLContext::OpenGLContext(SDL_Window* window)
    : window_{window}, context_{std::make_unique<SDL_GLContext>(
                           SDL_GL_CreateContext(window))}
{
    SGE_PROFILE_FUNCTION();

    int status = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    if (status == 0) {
        throw std::runtime_error("Could not init GLEW");
    }

    // glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
}

void OpenGLContext::swap_buffers()
{
    SGE_PROFILE_FUNCTION();

    SDL_GL_SwapWindow(window_);
    Renderer::clear_screen();
}

void OpenGLContext::delete_context()
{
    SDL_GL_DeleteContext(*context_);
}

} // namespace SGE
