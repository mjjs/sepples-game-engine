#ifndef _SGE_LINUX_WINDOW_H
#define _SGE_LINUX_WINDOW_H

#include "openglcontext.h"
#include "window.h"

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

    SDL_Window* window_;

    void poll_events() const;

  public:
    LinuxWindow(const std::string& title = default_window_title,
                std::uint32_t width      = default_window_width,
                std::uint32_t height     = default_window_height);

    ~LinuxWindow();

    LinuxWindow(const LinuxWindow&)  = delete;
    LinuxWindow(const LinuxWindow&&) = delete;
    LinuxWindow& operator=(const LinuxWindow&) = delete;
    LinuxWindow& operator=(const LinuxWindow&&) = delete;

    void update() override;

    std::uint32_t width() const override;
    std::uint32_t height() const override;

    void set_event_callback(const EventCallbackFn& callback) override;
    void* get_native_window() const override;
};

} // namespace SGE

#endif
