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
#include "uniformbuffer.h"

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

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
        static std::unique_ptr<GraphicsAPI> graphics_api_;
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
        static std::shared_ptr<UniformBuffer> camera_buffer_;

    public:
        static void init();
        static void clear_screen();
        static void set_clear_colour(const Vector3& colour);

        // OLD API

        void render(GameObject& gameobject);

        void set_camera(Camera* camera);
        Camera* camera() const;
        Light* active_light() const;
        void add_light(Light* light);

};

} // namespace SGE
#endif
