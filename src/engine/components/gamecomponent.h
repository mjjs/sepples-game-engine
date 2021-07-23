#ifndef _SGE_GAMECOMPONENT_H
#define _SGE_GAMECOMPONENT_H

#include "input.h"
#include "transform.h"
#include "shader.h"

#include <memory>

namespace SGE {

class RenderingEngine;
class GameObject;

class GameComponent {
    private:
        GameObject* parent_ = nullptr;

    public:
        GameComponent() = default;
        GameComponent(const GameComponent&) = default;
        GameComponent(GameComponent&&) = default;
        GameComponent& operator=(const GameComponent&) = default;
        GameComponent& operator=(GameComponent&&) = default;
        virtual ~GameComponent() = default;

        virtual void init();
        virtual void update(const Transform& transform, float delta);
        virtual void fixed_update(const Transform& transform);
        virtual void render(const Transform& transform, Shader& shader, const RenderingEngine& rendering_engine);
        virtual void add_to_rendering_engine(RenderingEngine& rendering_engine);

        void set_parent(GameObject* game_object);

        const Transform& get_transform() const;
};
} // namespace SGE
#endif
