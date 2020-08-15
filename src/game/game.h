#ifndef _GE_GAME_H
#define _GE_GAME_H

#include "input.h"
#include "level.h"
#include "player.h"

#include <memory>

namespace Game {
class Game {
    private:
        std::shared_ptr<Level> level_;
        Player player_;
        static inline bool is_running = true;

    public:
        Game();
        void update();
        void render();
        void input(const Input& inputs);

        static void game_over();
};
} // namespace Game
#endif
