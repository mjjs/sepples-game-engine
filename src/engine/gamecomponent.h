#ifndef _SGE_GAMECOMPONENT_H
#define _SGE_GAMECOMPONENT_H

#include "transform.h"

namespace SGE {
class GameComponent {
    public:
        GameComponent() = default;
        GameComponent(const GameComponent&) = default;
        GameComponent(GameComponent&&) = default;
        GameComponent& operator=(const GameComponent&) = default;
        GameComponent& operator=(GameComponent&&) = default;
        virtual ~GameComponent() = default;

        virtual void init() = 0;
        virtual void input(const Math::Transform& transform) = 0;
        virtual void update(const Math::Transform& transform) = 0;
        virtual void render(const Math::Transform& transform) = 0;
};
} // namespace SGE
#endif
