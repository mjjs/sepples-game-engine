#ifndef _SGE_TEST_GAME_H
#define _SGE_TEST_GAME_H

#include "camera.h"
#include "game.h"
#include "input.h"
#include "model.h"
#include "phongshader.h"
#include "transform.h"
#include "vector3.h"

class TestGame : public SGE::Game::Game {
    private:
        Camera camera_;
        PhongShader shader_;
        Model model_;
        Math::Transform transformer_;

        // For transform demonstrations
        float temp_ = 0.0F;

    public:
        TestGame();

        void update();
        void render();
        void input(const Input& inputs);
};
#endif
