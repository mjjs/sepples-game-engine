#include "camera.h"
#include "matrix4.h"
#include "renderingengine.h"
#include "sgemath.h"
#include "vector3.h"

namespace SGE {

Camera::Camera(
        const float fov_radians,
        const float aspect_ratio,
        const float z_near,
        const float z_far
        ) :
    projection_{Matrix4::perspective(fov_radians, aspect_ratio, z_near, z_far)}
{
}

Matrix4 Camera::get_view_projection() const
{
    const Matrix4 camera_rotation = get_transform().rotation().to_rotation_matrix();
    const Matrix4 camera_translation = Matrix4::translation(-1 * get_transform().position());

    return projection_ * (camera_rotation * camera_translation);
}

void Camera::move(const Vector3& direction, float amount)
{
    get_transform().set_position(
            get_transform().position() + (direction * amount)
            );
}

void Camera::rotate_x(float radians)
{
    get_transform().set_rotation(
            get_transform().rotation() * Quaternion{get_transform().rotation().get_right(), radians}.normalized()
            );
}

void Camera::rotate_y(float radians)
{
    get_transform().set_rotation(
            get_transform().rotation() * Quaternion{world_up_, radians}.normalized()
            );
}

void Camera::add_to_rendering_engine(RenderingEngine& rendering_engine)
{
    rendering_engine.set_camera(this);
}

void Camera::update(const float delta)
{
    const float move_speed = 25;
    const float rotate_speed = 90;

    if (Input::is_key_down(SDLK_w)) {
        move(get_transform().rotation().get_forward(), move_speed * delta);
    }

    if (Input::is_key_down(SDLK_s)) {
        move(get_transform().rotation().get_back(), move_speed * delta);
    }

    if (Input::is_key_down(SDLK_a)) {
        move(get_transform().rotation().get_left(), move_speed * delta);
    }

    if (Input::is_key_down(SDLK_d)) {
        move(get_transform().rotation().get_right(), move_speed * delta);
    }

    if (Input::is_key_down(SDLK_UP)) {
        rotate_x(to_radians(rotate_speed) * delta);
    }

    if (Input::is_key_down(SDLK_DOWN)) {
        rotate_x(to_radians(-rotate_speed) * delta);
    }

    if (Input::is_key_down(SDLK_LEFT)) {
        rotate_y(to_radians(rotate_speed) * delta);
    }

    if (Input::is_key_down(SDLK_RIGHT)) {
        rotate_y(to_radians(-rotate_speed) * delta);
    }
}

} // namespace SGE
