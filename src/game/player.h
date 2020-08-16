#ifndef _SGE_PLAYER_H
#define _SGE_PLAYER_H

#include "basicshader.h"
#include "camera.h"
#include "input.h"
#include "material.h"
#include "mesh.h"
#include "transform.h"
#include "vector3.h"

#include <chrono>
#include <memory>

namespace Game {
class Level;

class Player {
    private:
        const float speed_ = 0.05F;
        const float size_ = 0.2F;

        Level* level_;
        Math::Vector3 movement_vector_;

        Material gun_material_;
        Mesh gun_;
        Math::Transform gun_transform_;

        Material shoot_material_;
        Mesh shoot_;
        Math::Transform shoot_transform_;

        std::chrono::time_point<std::chrono::steady_clock> last_shot_ = std::chrono::steady_clock::now();

        static inline const float START = 0.0F;
        static inline const float SCALE = 0.0685F;
        static inline const float SIZE_Y = SCALE;
        static inline const float SIZE_X = SIZE_Y / (1.0379746835443037974683544303797 * 2.0);

        static inline const float OFFSET_X = 0.0F;
        static inline const float OFFSET_Y = 0.0F;

        static inline const float TEXTURE_MAX_X = -1 - OFFSET_X;
        static inline const float TEXTURE_MIN_X = -OFFSET_X;
        static inline const float TEXTURE_MAX_Y = 1 - OFFSET_Y;
        static inline const float TEXTURE_MIN_Y = -OFFSET_Y;

        int health_ = 100;

    public:
        Player();
        explicit Player(const Math::Vector3& initial_position);
        explicit Player(const Player& other);
        Player& operator=(const Player&);
        Player& operator=(Player&&);
        void input(const Input& inputs);
        void update();
        void render(BasicShader& shader);
        void set_level(Level* level);

        static inline std::shared_ptr<Camera> camera_ = std::make_shared<Camera>(Camera{});
        const static inline float SHOOT_DISTANCE = 1000.0F;
        const static inline float GUN_OFFSET = -0.0875F;
        const static inline int DAMAGE = 30;

        void damage(int amount);
        void heal(int amount);
        bool dead() const;
        int health() const;
};
} // namespace Game
#endif
