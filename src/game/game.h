#ifndef _GE_GAME_H
#define _GE_GAME_H

#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "vector3.h"

namespace Game {
class Game {
    private:
        Shader shader_;
        Mesh mesh_;
        Math::Transform transformer_;

        // For transform demonstrations
        float temp_ = 0.0F;

    public:
        Game();
        void input();
        void update();
        void render();
};
} // namespace Game
#endif
