#ifndef _SGE_GAMEOBJECT_H
#define _SGE_GAMEOBJECT_H

#include "camera.h"
#include "gamecomponent.h"
#include "input.h"
#include "transform.h"
#include "shader.h"

#include <memory>
#include <vector>

namespace SGE {
class RenderingEngine;

class GameObject {
    private:
        Math::Transform transform_{};
        std::vector<std::shared_ptr<GameObject>> children_{};
        std::vector<std::shared_ptr<GameComponent>> components_{};

    public:
        GameObject() = default;
        GameObject(const GameObject&) = default;
        GameObject(GameObject&&) = default;
        GameObject& operator=(const GameObject&) = default;
        GameObject& operator=(GameObject&&) = default;
        virtual ~GameObject() = default;

        virtual void update(float delta);
        virtual void fixed_update();
        virtual void render(Shader& shader, const RenderingEngine& rendering_engine);
        virtual void add_to_rendering_engine(RenderingEngine& rendering_engine) const;

        inline void add_child(std::shared_ptr<GameObject> child)
        {
            children_.push_back(child);
        }

        void add_component(std::shared_ptr<GameComponent> component);

        inline void set_transform(const Math::Transform& transform)
        {
            transform_ = transform;
        }

        inline Math::Transform& transform()
        {
            return transform_;
        }
};
} // namespace SGE
#endif
