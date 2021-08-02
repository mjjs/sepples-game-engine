#include "camera.h"
#include "light.h"
#include "gameobject.h"
#include "renderingengine.h"
#include "vector3.h"

#include <memory>

#include <glad/glad.h>

namespace SGE {

// NOLINTNEXTLINE
std::unique_ptr<GraphicsAPI> RenderingEngine::graphics_api_ = GraphicsAPI::create();

void RenderingEngine::clear_screen()
{
    graphics_api_->clear_screen();
}

void RenderingEngine::set_clear_colour(const Vector3& colour)
{
    graphics_api_->set_clear_colour(colour);
}

void RenderingEngine::render(GameObject& gameobject)
{
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
