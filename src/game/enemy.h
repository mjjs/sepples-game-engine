#ifndef _SGE_ENEMY_H
#define _SGE_ENEMY_H

#include "basicshader.h"
#include "material.h"
#include "mesh.h"
#include "transform.h"

enum EnemyState {
    IDLE,
    CHASE,
    ATTACK,
    DYING,
    DEAD,
};

namespace Game {
class Enemy {
    private:
        Material material_;
        Math::Transform transform_;

        EnemyState state_ = EnemyState::IDLE;

        static inline Mesh mesh_;
        static inline bool mesh_created_ = false;

        void idle();
        void chase();
        void attack();
        void dying();
        void dead();

        void face_camera();

    public:
        Enemy() = default;
        explicit Enemy(const Math::Transform& transform);

        void update();
        void render(BasicShader& shader);

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
};
} // namespace Game
#endif
