#ifndef _SGE_PLAYER_H
#define _SGE_PLAYER_H

#include "basicshader.h"
#include "camera.h"
#include "input.h"
#include "level.h"
#include "material.h"
#include "mesh.h"
#include "transform.h"
#include "vector3.h"

#include <memory>

namespace Game {
class Player {
    private:
        const float speed_ = 0.05F;
        const float size_ = 0.2F;

        std::shared_ptr<Level> level_;
        Math::Vector3 movement_vector_;

        Material gun_material_;
        Mesh gun_;
        Math::Transform gun_transform_;

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
        explicit Player(const Math::Vector3& initial_position);
        void input(const Input& inputs);
        void update();
        void render(BasicShader& shader);
        void set_level(std::shared_ptr<Level> level);

        static inline std::shared_ptr<Camera> camera_ = std::make_shared<Camera>(Camera{});
        const static inline float SHOOT_DISTANCE = 1000.0F;
        const static inline float GUN_OFFSET = -0.0875F;
        const static inline int DAMAGE = 30;

        void damage(int amount);
        bool dead() const;
};
} // namespace Game
#endif
