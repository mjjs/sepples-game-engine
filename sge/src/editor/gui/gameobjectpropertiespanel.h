#ifndef _SGE_GAME_OBJECT_PROPERTIES_PANEL_H
#define _SGE_GAME_OBJECT_PROPERTIES_PANEL_H

#include "engine/ecs/gameobject.h"
#include "engine/ecs/scene.h"
#include "scenehierarchypanel.h"

#include <memory>
#include <string>

namespace SGE
{

class GameObjectPropertiesPanel
{
  private:
    std::shared_ptr<SceneHierarchyPanel> scene_hierarchy_panel_;
    std::shared_ptr<Scene> scene_;

    void draw_components(GameObject game_object);

  public:
    GameObjectPropertiesPanel(
        const std::shared_ptr<SceneHierarchyPanel> scene_hierarchy_panel,
        const std::shared_ptr<Scene> scene)
        : scene_hierarchy_panel_{scene_hierarchy_panel}, scene_{scene}
    {
    }

    void render_imgui();
};

} // namespace SGE

#endif
