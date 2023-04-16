#include "platform/linux/linuxwindow.h"

#include "backends/imgui_impl_sdl.h"
#include "engine/core/log.h"
#include "engine/debug/profiler.h"
#include "engine/event/keypressedevent.h"
#include "engine/event/keyreleasedevent.h"
#include "engine/event/mousebuttonpressedevent.h"
#include "engine/event/mousebuttonreleasedevent.h"
#include "engine/event/mousemovedevent.h"
#include "engine/event/mousescrolledevent.h"
#include "engine/event/windowcloseevent.h"
#include "engine/event/windowminimizeevent.h"
#include "engine/event/windowresizeevent.h"
#include "engine/event/windowrestoreevent.h"
#include "engine/imgui/imguirenderer.h"

#include <SDL.h>
#include <stdexcept>

namespace SGE
{

LinuxWindow::LinuxWindow(const std::string& title, std::uint32_t width,
                         std::uint32_t height)
    : width_{width}, height_{height}, title_{title}
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG_ERROR(SDL_GetError());
        throw std::runtime_error("SDL init failed");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, width, height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (window_ == nullptr) {
        LOG_ERROR(SDL_GetError());
        throw std::runtime_error("Could not create SDL window");
    }

    // TODO: Move into vsync
    SDL_GL_SetSwapInterval(1);

    context_ = std::make_unique<OpenGLContext>(window_);
    imgui_renderer_ =
        std::make_unique<LinuxImguiRenderer>(window_, context_->raw_context());
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

void LinuxWindow::poll_events()
{
    SGE_PROFILE_FUNCTION();

    SDL_Event event;

    while (SDL_PollEvent(&event) == 1) {
        bool handled = imgui_renderer_->handle_event(event);

        switch (event.type) {
        case SDL_QUIT: {
            LOG_INFO("QUIT EVENT");
            WindowCloseEvent event;
            event_callback_(event);
            break;
        }

        case SDL_KEYDOWN: {
            const SDL_Keycode key_code = event.key.keysym.sym;
            KeyPressedEvent event{key_code};
            event.handled = handled;
            event_callback_(event);
            break;
        }

        case SDL_KEYUP: {
            const SDL_Keycode key_code = event.key.keysym.sym;
            KeyReleasedEvent event{key_code};
            event.handled = handled;
            event_callback_(event);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            const std::uint8_t mouse_button_code = event.button.button;
            MouseButtonPressedEvent event{mouse_button_code};
            event.handled = handled;
            event_callback_(event);
            break;
        }

        case SDL_MOUSEBUTTONUP: {
            const std::uint8_t mouse_button_code = event.button.button;
            MouseButtonReleasedEvent event{mouse_button_code};
            event.handled = handled;
            event_callback_(event);
            break;
        }

        case SDL_MOUSEMOTION: {
            auto x = event.motion.x;
            auto y = event.motion.y;

            MouseMovedEvent event{static_cast<float>(x), static_cast<float>(y)};
            event.handled = handled;
            event_callback_(event);
            break;
        }

        case SDL_MOUSEWHEEL: {
            auto x = event.wheel.x;
            auto y = event.wheel.y;

            MouseScrolledEvent event{static_cast<float>(x),
                                     static_cast<float>(y)};
            event.handled = handled;
            event_callback_(event);
            break;
        }

        case SDL_WINDOWEVENT: {
            dispatch_window_event(event.window);
            break;
        }
        }
    }
}

void LinuxWindow::dispatch_window_event(const SDL_WindowEvent& event)
{
    switch (event.event) {
    case SDL_WINDOWEVENT_CLOSE: {
        WindowCloseEvent event;
        event_callback_(event);
        break;
    }

    case SDL_WINDOWEVENT_RESIZED: {
        auto width  = event.data1;
        auto height = event.data2;

        width_  = width;
        height_ = height;

        WindowResizeEvent event{static_cast<unsigned int>(width),
                                static_cast<unsigned int>(height)};

        event_callback_(event);
        break;
    }

    case SDL_WINDOWEVENT_MINIMIZED: {
        LOG_INFO("Window minimized");
        WindowMinimizeEvent event{};
        event_callback_(event);
        break;
    }

    case SDL_WINDOWEVENT_RESTORED: {
        LOG_INFO("Window restored");
        WindowRestoreEvent event{};
        event_callback_(event);
        break;
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

void LinuxWindow::begin_imgui_rendering()
{
    imgui_renderer_->start_rendering();
}

void LinuxWindow::end_imgui_rendering()
{
    imgui_renderer_->end_rendering(width_, height_);
}

} // namespace SGE
