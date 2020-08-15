#ifndef _SGE_ENEMY_H
#define _SGE_ENEMY_H

#include "basicshader.h"
#include "material.h"
#include "mesh.h"
#include "vector3.h"
#include "transform.h"

#include <chrono>
#include <memory>

enum EnemyState {
    IDLE,
    CHASE,
    ATTACK,
    DYING,
    DEAD,
};

namespace Game {

class Level;

class Enemy {
    private:
        Material material_;
        Math::Transform transform_;
        std::shared_ptr<Level> level_;

        EnemyState state_ = EnemyState::IDLE;

        static inline Mesh mesh_;
        static inline bool mesh_created_ = false;

        bool can_look = false;

        void idle(const Math::Vector3& orientation, float distance_to_camera);
        void chase(const Math::Vector3& orientation, float distance_to_camera);
        void attack(const Math::Vector3& orientation, float distance_to_camera);
        void dying(const Math::Vector3& orientation, float distance_to_camera);
        void dead(const Math::Vector3& orientation, float distance_to_camera);

        void face_camera(const Math::Vector3& direction_to_camera);

        std::chrono::time_point<std::chrono::steady_clock> last_attack_;
        std::chrono::time_point<std::chrono::steady_clock> last_player_check_;

        bool alive_ = true;
        int health_ = 100;

    public:
        Enemy() = default;
        explicit Enemy(const Math::Transform& transform);

        void update();
        void render(BasicShader& shader);

        void set_level(std::shared_ptr<Level> level);

        static inline const float START = 0.0F;

        static inline const float SCALE = 0.7F;

        static inline const float SIZE_Y = SCALE;
        static inline const float SIZE_X = SIZE_Y / (1.9310344827586206896551724137931 * 2.0);

        static inline const float OFFSET_X = 0.0F;
        static inline const float OFFSET_Y = 0.0F;

        static inline const float TEXTURE_MAX_X = -1 - OFFSET_X;
        static inline const float TEXTURE_MIN_X = -OFFSET_X;
        static inline const float TEXTURE_MAX_Y = 1 - OFFSET_Y;
        static inline const float TEXTURE_MIN_Y = -OFFSET_Y;

        static inline const float MOVE_SPEED = 0.02F;
        static inline const float MOVE_STOP_DISTANCE = 1.0F;
        static inline const float SHOOT_DISTANCE = 1000.0F;

        static inline const float WIDTH = 0.2F;
        static inline const float LENGTH = 0.2F;

        void damage(int amount);
        Math::Vector2 size() const;
        Math::Transform& transform();
};
} // namespace Game
#endif
