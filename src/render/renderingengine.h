#ifndef _SGE_RENDERINGENGINE_H
#define _SGE_RENDERINGENGINE_H

#include "basicshader.h"
#include "camera.h"
#include "gameobject.h"
#include "window.h"

#include <cstddef>
#include <string>

namespace SGE {

class RenderingEngine {
    private:
        Window window_;
        Camera main_camera_;
        BasicShader shader_;


    public:
        void render(GameObject& gameobject);
        RenderingEngine(std::size_t width, std::size_t height, const std::string& window_title);

        void set_camera(const Camera& camera);
        const Camera& camera() const;
};

} // namespace SGE
#endif
