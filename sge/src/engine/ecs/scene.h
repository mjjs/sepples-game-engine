#ifndef _SGE_SCENE_H
#define _SGE_SCENE_H

#include "engine/rendering/shader.h"
#include "entt.hpp"

#include <memory>
#include <string>

namespace SGE
{

class GameObject;

class Scene
{
    friend class GameObject;

  private:
    entt::registry components_{};

    void script_update(float delta);
    void script_fixed_update();

    // TEMPORARY
    std::shared_ptr<Shader> shader_{Shader::create("res/shaders/basic")};

  public:
    void update(float delta);
    void fixed_update();
    GameObject add_game_object(const std::string& tag = "");
};

} // namespace SGE

#endif
