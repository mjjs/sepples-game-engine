#ifndef _SGE_RENDERINGENGINE_H
#define _SGE_RENDERINGENGINE_H

#include "ambientshader.h"
#include "directionalshader.h"
#include "pointshader.h"
#include "spotshader.h"
#include "directionallight.h"
#include "light.h"
#include "spotlight.h"
#include "pointlight.h"
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
        Camera main_camera_;
        AmbientShader ambient_shader_;

        std::vector<Light*> lights_{};
        Light* active_light_ = nullptr;

        const Math::Vector3 ambient_light_{0.2F, 0.2F, 0.2F};

    public:
        RenderingEngine(std::size_t width, std::size_t height, const std::string& window_title);
        void render(GameObject& gameobject);

        void set_camera(const Camera& camera);
        const Camera& camera() const;

        const Math::Vector3& ambient_light() const;
        Light* active_light() const;

        void add_light(Light* light);

        // TEMPORARY HACK
        void input(const Input& input, float delta);
        //DirectionalLight directional_light{
        //    {1.0F, 1.0F, 1.0F},
        //    {1.0F, 0.0F, 0.0F},
        //    1.0F,
        //};
        //PointLight point_light{
        //    {0, .1F, 0},
        //    {0, 0, 1},
        //    1.0F,
        //    0,
        //    0,
        //    1,
        //};
        //SpotLight spot_light{
        //    main_camera_.get_position(),
        //    main_camera_.get_forward(),
        //    {1, 1, 1},
        //    1.0F,
        //    std::cos(Math::to_radians(12.5F)),
        //    std::cos(Math::to_radians(17.5F)),
        //    1.0F,
        //    0.09F,
        //    0.032F,
        //};
};

} // namespace SGE
#endif
