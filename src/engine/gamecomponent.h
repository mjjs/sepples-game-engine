#ifndef _SGE_GAMECOMPONENT_H
#define _SGE_GAMECOMPONENT_H

#include "camera.h"
#include "input.h"
#include "transform.h"
#include "shader.h"

namespace SGE {
class GameComponent {
    public:
        GameComponent() = default;
        GameComponent(const GameComponent&) = default;
        GameComponent(GameComponent&&) = default;
        GameComponent& operator=(const GameComponent&) = default;
        GameComponent& operator=(GameComponent&&) = default;
        virtual ~GameComponent() = default;

        virtual void init() {};
        virtual void input(const Input& input, const Math::Transform& transform) {};
        virtual void update(const Math::Transform& transform, float delta) {};
        virtual void fixed_update(const Math::Transform& transform) {};
        virtual void render(const Math::Transform& transform, Shader& shader, const Camera& camera) {};
};
} // namespace SGE
#endif
