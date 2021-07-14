#ifndef _SGE_RENDERINGENGINE_H
#define _SGE_RENDERINGENGINE_H

#include "ambientshader.h"
#include "directionalshader.h"
#include "pointshader.h"
#include "directionallight.h"
#include "pointlight.h"
#include "camera.h"
#include "gameobject.h"
#include "window.h"
#include "input.h"
#include "vector3.h"

#include <cstddef>
#include <string>
#include <vector>

namespace SGE {

class RenderingEngine {
    private:
        Window window_;
        Camera main_camera_;
        AmbientShader shader_;
        DirectionalShader directional_shader_;
        PointShader point_shader_;

        std::vector<PointLight> point_lights_;

    public:
        void render(GameObject& gameobject);
        RenderingEngine(std::size_t width, std::size_t height, const std::string& window_title);

        void set_camera(const Camera& camera);
        const Camera& camera() const;

        // TEMPORARY HACK
        void input(const Input& input, float delta);
        const Math::Vector3 ambient_light{0.2F, 0.2F, 0.2F};
        DirectionalLight directional_light{
            {1.0F, 1.0F, 1.0F},
            {1.0F, 0.0F, 0.0F},
            1.0F,
        };
        PointLight point_light{
            {0, .1F, 0},
            {0, 0, 1},
            1.0F,
            0,
            0,
            1,
        };
};

} // namespace SGE
#endif
