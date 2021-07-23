#ifndef _SGE_RENDERINGENGINE_H
#define _SGE_RENDERINGENGINE_H

#include "light.h"
#include "camera.h"
#include "gameobject.h"
#include "window.h"
#include "input.h"
#include "vector3.h"
#include "sgemath.h"

#include <cstddef>
#include <string>
#include <vector>
#include <memory>

namespace SGE {

class RenderingEngine {
    private:
        Window window_;
        Camera* main_camera_ = nullptr;

        std::vector<Light*> lights_{};
        Light* active_light_ = nullptr;

    public:
        RenderingEngine(std::size_t width, std::size_t height, const std::string& window_title);
        void render(GameObject& gameobject);

        void set_camera(Camera* camera);
        Camera* camera() const;
        Light* active_light() const;
        void add_light(Light* light);
};

} // namespace SGE
#endif
