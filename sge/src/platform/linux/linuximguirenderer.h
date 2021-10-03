#ifndef _SGE_LINUX_IMGUI_RENDERER_H
#define _SGE_LINUX_IMGUI_RENDERER_H

#include "engine/imgui/imguirenderer.h"

#include <SDL2/SDL.h>
#include <utility>

namespace SGE
{

class LinuxImguiRenderer : public ImguiRenderer
{
  private:
    bool block_events_ = true;

  public:
    LinuxImguiRenderer(SDL_Window* window, void* context);
    ~LinuxImguiRenderer();

    LinuxImguiRenderer(const LinuxImguiRenderer&)  = delete;
    LinuxImguiRenderer(const LinuxImguiRenderer&&) = delete;
    LinuxImguiRenderer& operator=(const LinuxImguiRenderer&) = delete;
    LinuxImguiRenderer& operator=(const LinuxImguiRenderer&&) = delete;

    void start_rendering() const override;
    void end_rendering() const override;

    bool handle_event(SDL_Event& event) const;
    void set_event_blocking(bool should_block) override
    {
        block_events_ = should_block;
    }
};

} // namespace SGE

#endif
