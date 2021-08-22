#ifndef _SGE_LINUX_IMGUI_RENDERER_H
#define _SGE_LINUX_IMGUI_RENDERER_H

#include "engine/imgui/imguirenderer.h"

#include <SDL2/SDL.h>
#include <utility>

namespace SGE
{

class LinuxImguiRenderer : public ImguiRenderer
{
  public:
    LinuxImguiRenderer(SDL_Window* window, void* context);
    ~LinuxImguiRenderer();

    LinuxImguiRenderer(const LinuxImguiRenderer&)  = delete;
    LinuxImguiRenderer(const LinuxImguiRenderer&&) = delete;
    LinuxImguiRenderer& operator=(const LinuxImguiRenderer&) = delete;
    LinuxImguiRenderer& operator=(const LinuxImguiRenderer&&) = delete;

    void start_rendering() const override;
    std::pair<float, float> end_rendering() const override;

    bool handle_event(SDL_Event& event) const;
};

} // namespace SGE

#endif
