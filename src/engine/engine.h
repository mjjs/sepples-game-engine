#ifndef _SGE_ENGINE_H
#define _SGE_ENGINE_H

#include "event.h"
#include "windowcloseevent.h"
#include "renderingengine.h"
#include "testgame.h"
#include "window.h"

#include <cstddef>
#include <memory>
#include <string>

namespace SGE {
class Engine {
    private:
        std::unique_ptr<Window> window_;
        std::unique_ptr<SGE::Game> game_;

        RenderingEngine rendering_engine_;
        bool running_ = false;

        void render();
        void handle_event(Event& event);
        bool handle_window_close(WindowCloseEvent& event);

    public:
        Engine(std::size_t width, std::size_t height, const std::string& window_title);

        void load_game(std::unique_ptr<SGE::Game> game);
        void run();
};
} // namespace SGE
#endif
