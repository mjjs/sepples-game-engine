#ifndef _SGE_GAME_OBJECT_PROPERTIES_PANEL_H
#define _SGE_GAME_OBJECT_PROPERTIES_PANEL_H

#include "engine/ecs/gameobject.h"

namespace SGE
{

class GameObjectPropertiesPanel
{
  private:
    static void draw_components(GameObject game_object);

  public:
    static void render_imgui();
    static void render_imgui(GameObject game_object);
};

} // namespace SGE

#endif
