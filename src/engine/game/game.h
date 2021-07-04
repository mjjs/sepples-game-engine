#ifndef _SGE_GAME_H
#define _SGE_GAME_H

#include "camera.h"
#include "input.h"
#include "gameobject.h"
#include "shader.h"

#include <memory>

namespace SGE {
namespace Game {
class Game {
    private:
        std::shared_ptr<GameObject> root_{new GameObject{}};

    public:
        Game() = default;
        Game(const Game&) = default;
        Game(Game&&) = default;
        Game& operator=(const Game&) = default;
        Game& operator=(Game&&) = default;
        virtual ~Game() = default;

        virtual void init() = 0;
        virtual void update(float delta);
        virtual void fixed_update();
        virtual void render(Shader& shader, const Camera& camera);
        virtual void input(const Input& inputs);

        void set_root(std::shared_ptr<GameObject> gameobject);
        std::shared_ptr<GameObject> root();
};
} // namespace Game
} // namespace SGE
#endif
