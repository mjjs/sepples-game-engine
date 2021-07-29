#include "linuxwindow.h"
#include "windowcloseevent.h"

#include <stdexcept>
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace SGE {

LinuxWindow::LinuxWindow(
        const std::string& title,
        std::uint32_t width,
        std::uint32_t height
        )
    : width_{width}, height_{height}, title_{title}
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL init failed");
    }

    window_ = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_OPENGL
            );

    if (window_ == nullptr) {
        throw std::runtime_error("Could not create SDL window");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // TODO: Move into vsync
    SDL_GL_SetSwapInterval(1);

    context_ = SDL_GL_CreateContext(window_);
    // Is this needed?
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

LinuxWindow::~LinuxWindow()
{
    SDL_GL_DeleteContext(context_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void LinuxWindow::clear() const
{
    fill(0.0F, 0.0F, 0.0F, 1.0F);
}

void LinuxWindow::fill(const float r, const float g, const float b, const float a) const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LinuxWindow::flip() const
{
    SDL_GL_SwapWindow(window_);
}

void LinuxWindow::update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) == 1) {
        if (event.type == SDL_QUIT) {
            WindowCloseEvent event;
            event_callback_(event);
        }
    }

    flip();
    clear();
}

std::uint32_t LinuxWindow::width() const
{
    return width_;
}

std::uint32_t LinuxWindow::height() const
{
    return height_;
}

void* LinuxWindow::get_native_window() const
{
    return window_;
}

void LinuxWindow::set_event_callback(const EventCallbackFn& callback)
{
    event_callback_ = callback;
}

} // namespace SGE
