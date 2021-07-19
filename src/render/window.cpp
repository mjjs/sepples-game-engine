#include "vector2.h"
#include "window.h"

#include <stdexcept>

#include <GL/glew.h>
#include <SDL2/SDL.h>

Window::Window(const size_t width, const size_t height, const std::string& title) :
    width_{width},
    height_{height}
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL init failed");
    }

    window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, SDL_WINDOW_OPENGL);

    if (window_ == nullptr) {
        throw std::runtime_error("Could not create SDL window");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetSwapInterval(1);

    context_ = SDL_GL_CreateContext(window_);
	glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Could not init GLEW");
    }

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);

    clear();
}

Window::~Window()
{
    SDL_GL_DeleteContext(context_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Window::flip() const
{
    SDL_GL_SwapWindow(window_);
}

void Window::clear() const
{
    fill(0.0, 0.0, 0.0, 1.0);
}

void Window::fill(const float r, const float g, const float b, const float a) const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Math::Vector2 Window::get_center() const
{
    return Math::Vector2{
        static_cast<float>(width_)/2,
        static_cast<float>(height_)/2,
    };
}
