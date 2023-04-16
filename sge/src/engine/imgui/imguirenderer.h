#ifndef _SGE_IMGUI_RENDERER_H
#define _SGE_IMGUI_RENDERER_H

#include <cstdint>
#include <utility>

namespace SGE
{

class ImguiRenderer
{
  public:
    ImguiRenderer()          = default;
    virtual ~ImguiRenderer() = default;

    ImguiRenderer(const ImguiRenderer&)             = delete;
    ImguiRenderer(const ImguiRenderer&&)            = delete;
    ImguiRenderer& operator=(const ImguiRenderer&)  = delete;
    ImguiRenderer& operator=(const ImguiRenderer&&) = delete;

    virtual void start_rendering() const                   = 0;
    virtual void end_rendering(std::uint32_t width,
                               std::uint32_t height) const = 0;
    virtual void set_event_blocking(bool should_block)     = 0;
};

} // namespace SGE

#endif
