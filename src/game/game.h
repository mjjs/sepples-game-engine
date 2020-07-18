#ifndef _GE_GAME_H
#define _GE_GAME_H

#include "camera.h"
#include "input.h"
#include "model.h"
#include "phongshader.h"
#include "transform.h"
#include "vector3.h"

namespace Game {
class Game {
    private:
        Camera camera_;
        PhongShader shader_;
        Model model_;
        Math::Transform transformer_;

        // For transform demonstrations
        float temp_ = 0.0F;

    public:
        Game();
        void update();
        void render();
        void input(const Input& inputs);
};
} // namespace Game
#endif
