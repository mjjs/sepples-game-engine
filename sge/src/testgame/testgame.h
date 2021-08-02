#ifndef _SGE_TEST_GAME_H
#define _SGE_TEST_GAME_H

#include "camera.h"
#include "game.h"
#include "gameobject.h"
#include "input.h"
#include "vector3.h"

class TestGame : public SGE::Game {
    public:
        TestGame();

        void init() override;
};
#endif
