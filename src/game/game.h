#ifndef _SGE_GAME_H
#define _SGE_GAME_H

#include "input.h"

namespace SGE {
namespace Game {
class Game {
    public:
        Game() = default;
        Game(const Game&) = default;
        Game(Game&&) = default;
        Game& operator=(const Game&) = default;
        Game& operator=(Game&&) = default;
        virtual ~Game() = default;

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void input(const Input& inputs) = 0;
};
} // namespace Game
} // namespace SGE
#endif
