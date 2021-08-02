#ifndef _SGE_RENDERINGENGINE_H
#define _SGE_RENDERINGENGINE_H

#include "graphicsapi.h"

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

        static std::unique_ptr<GraphicsAPI> graphics_api_;

    public:
        void render(GameObject& gameobject);

        void set_camera(Camera* camera);
        Camera* camera() const;
        Light* active_light() const;
        void add_light(Light* light);

        static void clear_screen();
        static void set_clear_colour(const Vector3& colour);
};

} // namespace SGE
#endif
