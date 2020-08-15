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

        int health_ = 100;

    public:
        explicit Player(const Math::Vector3& initial_position);
        void input(const Input& inputs);
        void update();
        void render();
        void set_level(std::shared_ptr<Level> level);

        static inline std::shared_ptr<Camera> camera_ = std::make_shared<Camera>(Camera{});
        const static inline float SHOOT_DISTANCE = 1000.0F;
        const static inline int DAMAGE = 30;

        void damage(int amount);
        bool dead() const;
};
} // namespace Game
#endif
