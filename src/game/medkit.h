#ifndef _GE_MEDKIT_H
#define _GE_MEDKIT_H

#include "basicshader.h"
#include "camera.h"
#include "material.h"
#include "mesh.h"
#include "player.h"
#include "transform.h"
#include "vector3.h"

namespace Game {
class Medkit {
    private:
        static inline Mesh mesh_;
        static inline Material material_;
        static inline bool mesh_created_ = false;

        Math::Transform transform_;
        Player* player_;

        const float PICKUP_DISTANCE = 0.5F;
        bool used_ = false;

    public:
        explicit Medkit(const Math::Transform& transform, Player* player);
        Medkit(const Medkit& medkit);
        Medkit& operator=(Medkit&& medkit);
        void render(BasicShader& shader);
        void update();
        Math::Transform& transform();

        static inline const float START = 0.0F;

        static inline const float SCALE = 0.4F;

        static inline const float SIZE_Y = SCALE;
        static inline const float SIZE_X = SIZE_Y / (0.67857142857142857142857142857143 * 4.0);

        static inline const float OFFSET_X = 0.0F;
        static inline const float OFFSET_Y = 0.0F;

        static inline const float TEXTURE_MAX_X = -1 - OFFSET_X;
        static inline const float TEXTURE_MIN_X = -OFFSET_X;
        static inline const float TEXTURE_MAX_Y = 1 - OFFSET_Y;
        static inline const float TEXTURE_MIN_Y = -OFFSET_Y;

        bool used();
};
} // namespace Game
#endif
