#ifndef _SGE_SCENE_H
#define _SGE_SCENE_H

#include "engine/rendering/shader.h"
#include "entt.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

namespace SGE
{

class GameObject;

class Scene
{
    friend class GameObject;
    friend class SceneHierarchyPanel;

  private:
    entt::registry components_{};

    void script_update(float delta);
    void script_fixed_update();

    std::unordered_map<std::string, std::uint32_t> reserved_names_{};
    std::string get_unique_name(const std::string& name);

    // TEMPORARY
    std::shared_ptr<Shader> shader_{Shader::create("res/shaders/basic")};

  public:
    void update(float delta);
    void fixed_update();

    void on_window_resized(std::uint32_t width, std::uint32_t height);
    GameObject add_game_object(const std::string& tag = "");
};

} // namespace SGE

#endif
