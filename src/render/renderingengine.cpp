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
    window_{width, height, window_title},
    main_camera_{Math::to_radians(70), static_cast<float>(width)/static_cast<float>(height), .1, 1000}
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

void RenderingEngine::set_camera(const Camera& camera)
{
    main_camera_ = camera;
}

const Camera& RenderingEngine::camera() const
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

// TEMPORARY HACK
void RenderingEngine::update(const float delta)
{
    const float move_speed = .025;

    if (Input::is_key_down(SDL_SCANCODE_D)) {
        main_camera_.move(main_camera_.get_right(), move_speed * delta);
    }

    if (Input::is_key_down(SDL_SCANCODE_A)) {
        main_camera_.move(main_camera_.get_left(), move_speed * delta);
    }

    if (Input::is_key_down(SDL_SCANCODE_W)) {
        main_camera_.move(main_camera_.get_forward(), move_speed * delta);
    }

    if (Input::is_key_down(SDL_SCANCODE_S)) {
        main_camera_.move(main_camera_.get_forward(), -move_speed * delta);
    }

    if (Input::is_key_down(SDL_SCANCODE_UP)) {
        main_camera_.rotate_x(-1);
    }

    if (Input::is_key_down(SDL_SCANCODE_DOWN)) {
        main_camera_.rotate_x(1);
    }

    if (Input::is_key_down(SDL_SCANCODE_LEFT)) {
        main_camera_.rotate_y(-1);
    }

    if (Input::is_key_down(SDL_SCANCODE_RIGHT)) {
        main_camera_.rotate_y(1);
    }
}

} // namespace SGE
