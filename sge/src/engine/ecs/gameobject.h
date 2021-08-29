#ifndef _SGE_GAMEOBJECT_H
#define _SGE_GAMEOBJECT_H

#include "engine/ecs/scene.h"
#include "entt.hpp"

#include <cassert>
#include <utility>

namespace SGE
{

class GameObject
{
  private:
    entt::entity id_{entt::null};
    Scene* scene_{nullptr};

  public:
    GameObject() = default;
    GameObject(entt::entity id, Scene* scene) : id_{id}, scene_{scene}
    {
    }

    template <typename ComponentType, typename... Args>
    ComponentType& add_component(Args&&... args)
    {
        assert(!has_component<ComponentType>());
        assert(scene_ != nullptr);

        ComponentType& component = scene_->components_.emplace<ComponentType>(
            id_, std::forward<Args>(args)...);

        return component;
    }

    template <typename ComponentType>
    ComponentType& get_component()
    {
        assert(has_component<ComponentType>());
        return scene_->components_.get<ComponentType>(id_);
    }

    template <typename ComponentType>
    bool has_component()
    {
        return scene_->components_.all_of<ComponentType>(id_);
    }

    template <typename ComponentType>
    void remove_component()
    {
        assert(has_component<ComponentType>());
        scene_->components_.remove<ComponentType>(id_);
    }

    bool operator==(const GameObject& other) const
    {
        return id_ == other.id_ && scene_ == other.scene_;
    }

    bool operator!=(const GameObject& other) const
    {
        return !(*this == other);
    }
};

} // namespace SGE

#endif
