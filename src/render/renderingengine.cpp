#include "camera.h"
#include "input.h"
#include "light.h"
#include "gameobject.h"
#include "renderingengine.h"
#include "sgemath.h"
#include "vector3.h"

#include <GL/glew.h>
#include <SDL2/SDL_scancode.h>
#include <cstddef>
#include <string>
#include <memory>

namespace SGE {

RenderingEngine::RenderingEngine(
        const std::size_t width,
        const std::size_t height,
        const std::string& window_title) :
    window_{width, height, window_title}
    //main_camera_{to_radians(70), static_cast<float>(width)/static_cast<float>(height), .1, 1000}
{
}

void RenderingEngine::render(GameObject& gameobject)
{
    window_.clear();

    // TODO: Make light list persistent instead of clearing and re-adding
    // all lights every frame.
    lights_.clear();
    gameobject.add_to_rendering_engine(*this);

    bool first_pass = true;

    for (Light* light : lights_) {
        if (!first_pass) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);
            glDepthMask(GL_FALSE);
            glDepthFunc(GL_EQUAL);
        }

        active_light_ = light;
        gameobject.render(*light->shader(), *this);

        first_pass = false;
    }

    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    window_.flip();
}

void RenderingEngine::set_camera(Camera* camera)
{
    main_camera_ = camera;
}

Camera* RenderingEngine::camera() const
{
    return main_camera_;
}

Light* RenderingEngine::active_light() const
{
    return active_light_;
}

void RenderingEngine::add_light(Light* light)
{
    lights_.push_back(light);
}

} // namespace SGE
