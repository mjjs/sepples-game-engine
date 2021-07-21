#ifndef _SGE_GAME_H
#define _SGE_GAME_H

#include "camera.h"
#include "input.h"
#include "gameobject.h"
#include "shader.h"
#include "renderingengine.h"

#include <memory>

namespace SGE {

class Game {
    private:
        std::shared_ptr<GameObject> root_ = std::make_shared<GameObject>();

    public:
        Game() = default;
        Game(const Game&) = default;
        Game(Game&&) = default;
        Game& operator=(const Game&) = default;
        Game& operator=(Game&&) = default;
        virtual ~Game() = default;

        virtual void init() = 0;

        inline virtual void update(float delta)
        {
            root_->update(delta);
        }

        inline virtual void fixed_update()
        {
            root_->fixed_update();
        }

        inline virtual void render(Shader& shader, const RenderingEngine& rendering_engine)
        {
            root_->render(shader, rendering_engine);
        }

        inline void set_root(std::shared_ptr<GameObject> gameobject)
        {
            root_ = gameobject;
        }

        inline std::shared_ptr<GameObject> root()
        {
            return root_;
        }
};
} // namespace SGE
#endif
