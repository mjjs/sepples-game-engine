#include <stdexcept>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "window.h"

Window::Window(const size_t width, const size_t height, const std::string& title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL init failed");
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, SDL_WINDOW_OPENGL);

    if (window == nullptr) {
        throw std::runtime_error("Could not create SDL window");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetSwapInterval(1);

    context = SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Could not init GLEW");
    }

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    clear();
}

void Window::cleanup()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::flip()
{
    SDL_GL_SwapWindow(window);
}

void Window::clear()
{
    fill(0.0, 0.0, 0.0, 1.0);
}

void Window::fill(const float r, const float g, const float b, const float a) const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
