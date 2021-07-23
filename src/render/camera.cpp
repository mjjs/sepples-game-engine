#include "camera.h"
#include "sgemath.h"
#include "vector3.h"
#include "matrix4.h"

namespace SGE {

Camera::Camera(
        const float fov_radians,
        const float aspect_ratio, 
        const float z_near,
        const float z_far
        ) :
    position_{Vector3{0,0,0}},
    forward_{Vector3{0,0,1}},
    up_{Vector3{0,1,0}},
    projection_{Matrix4::perspective(fov_radians, aspect_ratio, z_near, z_far)}
{
}

Matrix4 Camera::get_view_projection() const
{
    const Matrix4 camera_rotation = Matrix4::camera(forward_, up_);
    const Matrix4 camera_translation = Matrix4::translation(-1 * position_);

    return projection_ * camera_rotation * camera_translation;
}

void Camera::move(const Vector3& direction, float amount)
{
    position_ = position_ + amount * direction;
}

void Camera::rotate_x(float radians)
{
    Vector3 horizontal_axis = world_up_.cross(forward_).normalized();

    forward_ = forward_.rotate(radians, horizontal_axis).normalized();

    up_ = forward_.cross(horizontal_axis).normalized();
}

void Camera::rotate_y(float radians)
{
    Vector3 horizontal_axis = normalize(cross(world_up_, forward_));

    forward_ = forward_.rotate(radians, world_up_).normalized();

    up_ = forward_.cross(horizontal_axis).normalized();
}

Vector3 Camera::get_position() const
{
    return position_;
}

Vector3 Camera::get_left() const
{
    return forward_.cross(up_).normalized();
}

Vector3 Camera::get_right() const
{
    return up_.cross(forward_).normalized();
}

Vector3 Camera::get_forward() const
{
    return forward_;
}

Vector3 Camera::get_up() const
{
    return up_;
}

} // namespace SGE
