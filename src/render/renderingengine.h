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
        Camera* main_camera_ = nullptr;

        std::vector<Light*> lights_{};
        Light* active_light_ = nullptr;

    public:
        void render(GameObject& gameobject);

        void set_camera(Camera* camera);
        Camera* camera() const;
        Light* active_light() const;
        void add_light(Light* light);
};

} // namespace SGE
#endif
