#ifndef _GE_GAME_H
#define _GE_GAME_H

#include "input.h"
#include "basicshader.h"

namespace Game {
class Game {
    private:
        BasicShader shader_;

    public:
        Game();
        void update();
        void render();
        void input(const Input& inputs);
};
} // namespace Game
#endif
