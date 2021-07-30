#include "linuxwindow.h"
#include "keypressedevent.h"
#include "keyreleasedevent.h"
#include "mousebuttonpressedevent.h"
#include "mousebuttonreleasedevent.h"
#include "mousemovedevent.h"
#include "mousescrolledevent.h"
#include "windowcloseevent.h"
#include "log.h"

#include <stdexcept>
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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

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

    // TODO: Move into vsync
    SDL_GL_SetSwapInterval(1);

    context_ = std::make_unique<OpenGLContext>(window_);
}

LinuxWindow::~LinuxWindow()
{
    context_->delete_context();
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void LinuxWindow::update()
{
    poll_events();
    context_->swap_buffers();
}

void LinuxWindow::poll_events() const
{
    SDL_Event event;

    while (SDL_PollEvent(&event) == 1) {
        switch (event.type) {
        case SDL_QUIT: {
            WindowCloseEvent event;
            event_callback_(event);
            break;
        }

        case SDL_KEYDOWN: {
            const SDL_Keycode key_code = event.key.keysym.sym;
            KeyPressedEvent event{key_code};
            event_callback_(event);
            break;
        }

        case SDL_KEYUP: {
            const SDL_Keycode key_code = event.key.keysym.sym;
            KeyReleasedEvent event{key_code};
            event_callback_(event);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            const std::uint8_t mouse_button_code = event.button.button;
            MouseButtonPressedEvent event{mouse_button_code};
            event_callback_(event);
            break;
        }

        case SDL_MOUSEBUTTONUP: {
            const std::uint8_t mouse_button_code = event.button.button;
            MouseButtonReleasedEvent event{mouse_button_code};
            event_callback_(event);
            break;
        }

        case SDL_MOUSEMOTION: {
            auto x = event.motion.x;
            auto y = event.motion.y;

            MouseMovedEvent event{Vector2{static_cast<float>(x), static_cast<float>(y)}};
            event_callback_(event);
        }

        case SDL_MOUSEWHEEL: {
            auto x = event.wheel.x;
            auto y = event.wheel.y;

            MouseScrolledEvent event{Vector2{static_cast<float>(x), static_cast<float>(y)}};
            event_callback_(event);
        }

        }
    }
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
