#ifndef _SGE_PLAYER_H
#define _SGE_PLAYER_H

#include "camera.h"
#include "input.h"
#include "level.h"
#include "vector3.h"

#include <memory>

namespace Game {
class Player {
    private:
        const float speed_ = 0.05F;
        const float size_ = 0.2F;

        std::shared_ptr<Level> level_;
        Math::Vector3 movement_vector_;

    public:
        explicit Player(const Math::Vector3& initial_position);
        void input(const Input& inputs);
        void update();
        void render();
        void set_level(std::shared_ptr<Level> level);

        static inline std::shared_ptr<Camera> camera_ = std::make_shared<Camera>(Camera{});

};
} // namespace Game
#endif
