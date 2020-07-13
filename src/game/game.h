#ifndef _GE_GAME_H
#define _GE_GAME_H

#include "camera.h"
#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "vector3.h"

namespace Game {
class Game {
    private:
        Camera camera_;
        Shader shader_;
        Mesh mesh_;
        Math::Transform transformer_;

        // For transform demonstrations
        float temp_ = 0.0F;

    public:
        Game();
        void update();
        void render();
};
} // namespace Game
#endif
