#ifndef _SGE_CAMERACONTROLLER_H
#define _SGE_CAMERACONTROLLER_H

#include "sge.h"

namespace SGE
{

class CameraScript : public Scriptable
{
  private:
    const float camera_move_speed_   = 25;
    const float camera_rotate_speed_ = 90;

  public:
    void update(const float delta) override
    {
        auto& transform = get_component<TransformComponent>().transform();
        const auto& camera_rot = transform.rotation();

        auto front = camera_rot * glm::vec3{0, 0, -1};
        auto right = camera_rot * glm::vec3{1, 0, 0};

        const auto amount = camera_move_speed_ * delta;

        if (Input::is_key_down(SDLK_w)) {
            transform.set_position(transform.position() + (front * amount));
        }

        if (Input::is_key_down(SDLK_s)) {
            transform.set_position(transform.position() + (front * -amount));
        }

        if (Input::is_key_down(SDLK_a)) {
            transform.set_position(transform.position() + (right * -amount));
        }

        if (Input::is_key_down(SDLK_d)) {
            transform.set_position(transform.position() + (right * amount));
        }

        if (Input::is_key_down(SDLK_UP)) {
            auto angle = glm::radians(camera_rotate_speed_ * delta);
            auto rot   = glm::angleAxis(angle, glm::vec3{1, 0, 0});
            transform.set_rotation(transform.rotation() * rot);
        }

        if (Input::is_key_down(SDLK_DOWN)) {
            auto angle = -glm::radians(camera_rotate_speed_ * delta);
            auto rot   = glm::angleAxis(angle, glm::vec3{1, 0, 0});
            transform.set_rotation(transform.rotation() * rot);
        }

        if (Input::is_key_down(SDLK_LEFT)) {
            auto angle = glm::radians(camera_rotate_speed_ * delta);
            auto rot   = glm::angleAxis(angle, glm::vec3{0, 1, 0});
            transform.set_rotation(rot * transform.rotation());
        }

        if (Input::is_key_down(SDLK_RIGHT)) {
            auto angle = -glm::radians(camera_rotate_speed_ * delta);
            auto rot   = glm::angleAxis(angle, glm::vec3{0, 1, 0});
            transform.set_rotation(rot * transform.rotation());
        }
    }

    void fixed_update() override
    {
    }
};

} // namespace SGE
#endif
