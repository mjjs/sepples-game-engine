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

    // TEMPORARY
    std::shared_ptr<Shader> shader_{Shader::create("res/shaders/basic")};

  public:
    void update(float delta);
    GameObject add_game_object(const std::string& tag = "");
};

} // namespace SGE

#endif
