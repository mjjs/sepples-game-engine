#ifndef _SGE_ENGINE_H
#define _SGE_ENGINE_H

#include "renderingengine.h"
#include "testgame.h"
#include "window.h"

#include <cstddef>
#include <memory>
#include <string>

namespace SGE {
class Engine {
    private:
        bool running_ = false;

        RenderingEngine rendering_engine_;
        std::unique_ptr<SGE::Game> game_;

        void render();

    public:
        Engine(std::size_t width, std::size_t height, const std::string& window_title);

        void load_game(std::unique_ptr<SGE::Game> game);
        void run();
};
} // namespace SGE
#endif
