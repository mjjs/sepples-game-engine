#ifndef _SGE_PLAYER_H
#define _SGE_PLAYER_H

#include "camera.h"
#include "input.h"
#include "vector3.h"

#include <memory>

namespace Game {
class Player {
    private:
        std::shared_ptr<Camera> camera_;
        const float speed_ = 0.08F;

    public:
        explicit Player(const Math::Vector3& initial_position);
        void input(const Input& inputs);
        void update();
        void render();
        std::shared_ptr<Camera> camera() const;

};
} // namespace Game
#endif
