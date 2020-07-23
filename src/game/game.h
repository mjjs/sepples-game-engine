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

    public:
        Game();
        void update();
        void render();
        void input(const Input& inputs);
};
} // namespace Game
#endif
