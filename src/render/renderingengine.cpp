#include "camera.h"
#include "gameobject.h"
#include "renderingengine.h"
#include "sgemath.h"
#include "vector3.h"

#include <GL/glew.h>
#include <cstddef>
#include <string>

SGE::RenderingEngine::RenderingEngine(
        const std::size_t width,
        const std::size_t height,
        const std::string& window_title) :
    window_{width, height, window_title},
    main_camera_{Math::to_radians(70), static_cast<float>(width)/static_cast<float>(height), .1, 1000}
{
    // More hacks for light testing
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            point_lights_.push_back(
                PointLight{
                    {static_cast<float>(0 + 5 * i), .1F,  static_cast<float>(0 + 5 * j)},
                    {static_cast<float>(.5*i), static_cast<float>(.5*j), static_cast<float>(.5 * i)},
                    2.0F,
                    1,
                    0,
                    1,
                }
            );
        }
    }

    point_light = point_lights_[0];
}

void SGE::RenderingEngine::render(GameObject& gameobject)
{
    window_.clear();

    gameobject.render(shader_, *this);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_EQUAL);

    gameobject.render(directional_shader_, *this);
    directional_light.colour = {0, 0, 1};
    directional_light.direction = {-8, 1, -5};
    gameobject.render(directional_shader_, *this);
    directional_light.colour = {1.0F, 0.0F, 0};
    directional_light.direction = {8, 1, 5};

    for (const auto& pl : point_lights_) {
        point_light = pl;
        gameobject.render(point_shader_, *this);
    }

    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

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

// TEMPORARY HACK
void SGE::RenderingEngine::input(const Input& input, const float delta)
{
    const float move_speed = .025;

    if (input.is_key_down(SDLK_d)) {
        main_camera_.move(main_camera_.get_right(), move_speed * delta);
    }

    if (input.is_key_down(SDLK_a)) {
        main_camera_.move(main_camera_.get_left(), move_speed * delta);
    }

    if (input.is_key_down(SDLK_w)) {
        main_camera_.move(main_camera_.get_forward(), move_speed * delta);
    }

    if (input.is_key_down(SDLK_s)) {
        main_camera_.move(main_camera_.get_forward(), -move_speed * delta);
    }

    if (input.is_key_down(SDLK_UP)) {
        main_camera_.rotate_x(-1);
    }

    if (input.is_key_down(SDLK_DOWN)) {
        main_camera_.rotate_x(1);
    }

    if (input.is_key_down(SDLK_LEFT)) {
        main_camera_.rotate_y(-1);
    }

    if (input.is_key_down(SDLK_RIGHT)) {
        main_camera_.rotate_y(1);
    }
}
