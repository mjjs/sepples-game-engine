#ifndef _SGE_EDITOR_H
#define _SGE_EDITOR_H

#include "gui/scenehierarchypanel.h"
#include "sge.h"

#include <cstdint>

namespace SGE
{

class Editor : public Game
{
  private:
    std::shared_ptr<Scene> active_scene_;
    std::shared_ptr<Framebuffer> framebuffer_;

    std::uint32_t scene_viewport_width_  = 0;
    std::uint32_t scene_viewport_height_ = 0;

    SceneHierarchyPanel scene_hierarchy_panel_;

  public:
    Editor();

    void update(float delta) override;
    void render_imgui() override;
    void on_viewport_resize(std::size_t width, std::size_t height) override;
};

} // namespace SGE

#endif
