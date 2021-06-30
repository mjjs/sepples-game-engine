#ifndef _SGE_RENDERINGENGINE_H
#define _SGE_RENDERINGENGINE_H

#include "gameobject.h"
#include "window.h"

#include <cstddef>
#include <string>

namespace SGE {

class RenderingEngine {
    private:
        Window window_;

    public:
        void render(const GameObject& gameobject) const;
        RenderingEngine(std::size_t width, std::size_t height, const std::string& window_title);
};

} // namespace SGE
#endif
