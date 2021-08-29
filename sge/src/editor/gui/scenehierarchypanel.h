#ifndef _SGE_SCENE_HIERARCHY_PANEL_H
#define _SGE_SCENE_HIERARCHY_PANEL_H

#include "engine/ecs/gameobject.h"
#include "engine/ecs/scene.h"

#include <memory>

namespace SGE
{

class SceneHierarchyPanel
{
  private:
    std::shared_ptr<Scene> scene_;
    GameObject selected_game_object_;

    void draw_game_object_node(GameObject game_object);

  public:
    SceneHierarchyPanel() = default;
    SceneHierarchyPanel(const std::shared_ptr<Scene>& scene);

    void render_imgui();
};

} // namespace SGE

#endif
