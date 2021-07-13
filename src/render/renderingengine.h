#ifndef _SGE_RENDERINGENGINE_H
#define _SGE_RENDERINGENGINE_H

#include "ambientshader.h"
#include "directionalshader.h"
#include "directionallight.h"
#include "camera.h"
#include "gameobject.h"
#include "window.h"
#include "input.h"
#include "vector3.h"

#include <cstddef>
#include <string>

namespace SGE {

class RenderingEngine {
    private:
        Window window_;
        Camera main_camera_;
        AmbientShader shader_;
        DirectionalShader directional_shader_;

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
};

} // namespace SGE
#endif
