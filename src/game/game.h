#ifndef _GE_GAME_H
#define _GE_GAME_H

#include "basicshader.h"
#include "input.h"
#include "level.h"
#include "player.h"

#include <memory>

namespace Game {
class Game {
    private:
        std::shared_ptr<Level> level_;
        static inline bool is_running = true;
        BasicShader shader_;
        static inline int level_number_ = 0;

    public:
        Game();
        void update();
        void render();
        void input(const Input& inputs);

        static void game_over();
        static void load_next_level();
};
} // namespace Game
#endif
