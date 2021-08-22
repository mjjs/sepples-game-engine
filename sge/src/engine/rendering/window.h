#ifndef _SGE_WINDOW_H
#define _SGE_WINDOW_H

#include "engine/event/event.h"
#include "engine/imgui/imguirenderer.h"
#include "engine/rendering/renderingcontext.h"

#include <cstdint>
#include <memory>
#include <string>

namespace SGE
{

class Window
{
  protected:
    static constexpr std::uint32_t default_window_width  = 1270;
    static constexpr std::uint32_t default_window_height = 800;
    static constexpr auto default_window_title = "Sepples Game Engine";

  public:
    Window()          = default;
    virtual ~Window() = default;

    Window(const Window&)  = delete;
    Window(const Window&&) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(const Window&&) = delete;

    virtual void update()                = 0;
    virtual void begin_imgui_rendering() = 0;
    virtual void end_imgui_rendering()   = 0;

    virtual std::uint32_t width() const     = 0;
    virtual std::uint32_t height() const    = 0;
    virtual void* get_native_window() const = 0;

    virtual void set_event_callback(const EventCallbackFn& callback) = 0;

    static std::unique_ptr<Window> create(
        const std::string& title = default_window_title,
        std::uint32_t width      = default_window_width,
        std::uint32_t height     = default_window_height);
};

} // namespace SGE
#endif
