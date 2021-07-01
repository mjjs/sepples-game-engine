#include "basicshader.h"
#include "camera.h"
#include "gameobject.h"
#include "renderingengine.h"
#include "sgemath.h"

#include <cstddef>
#include <string>

SGE::RenderingEngine::RenderingEngine(
        const std::size_t width,
        const std::size_t height,
        const std::string& window_title) :
    window_{width, height, window_title},
    main_camera_{Math::to_radians(70), static_cast<float>(width)/static_cast<float>(height), .1, 1000}
{
}

void SGE::RenderingEngine::render(GameObject& gameobject)
{
    window_.clear();

    gameobject.render(shader_, main_camera_);

    window_.flip();
}

void SGE::RenderingEngine::set_camera(const Camera& camera)
{
    main_camera_ = camera;
}

const Camera& SGE::RenderingEngine::camera() const
{
    return main_camera_;
}
