#ifndef _SGE_LINUX_WINDOW_H
#define _SGE_LINUX_WINDOW_H

#include "engine/imgui/imguirenderer.h"
#include "engine/rendering/renderingcontext.h"
#include "engine/rendering/window.h"
#include "platform/linux/linuximguirenderer.h"
#include "platform/opengl/openglcontext.h"

#include <cstdint>
#include <memory>
#include <string>

struct SDL_Window;

namespace SGE
{

class LinuxWindow : public Window
{
  private:
    std::uint32_t width_;
    std::uint32_t height_;
    std::string title_;

    EventCallbackFn event_callback_;
    std::unique_ptr<OpenGLContext> context_;
    std::unique_ptr<LinuxImguiRenderer> imgui_renderer_;

    SDL_Window* window_;

    void poll_events();
    void dispatch_window_event(const SDL_WindowEvent& event);

  public:
    LinuxWindow(const std::string& title = default_window_title,
                std::uint32_t width      = default_window_width,
                std::uint32_t height     = default_window_height);

    ~LinuxWindow() override;

    LinuxWindow(const LinuxWindow&)             = delete;
    LinuxWindow(const LinuxWindow&&)            = delete;
    LinuxWindow& operator=(const LinuxWindow&)  = delete;
    LinuxWindow& operator=(const LinuxWindow&&) = delete;

    void update() override;

    std::uint32_t width() const override;
    std::uint32_t height() const override;

    void begin_imgui_rendering() override;
    void end_imgui_rendering() override;

    void set_event_callback(const EventCallbackFn& callback) override;

    void* get_native_window() const override;

    void set_block_imgui_events(const bool should_block) override
    {
        imgui_renderer_->set_event_blocking(should_block);
    }
};

} // namespace SGE

#endif
