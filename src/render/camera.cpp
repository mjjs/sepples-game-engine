#include "camera.h"
#include "gemath.h"
#include "vector3.h"

Camera::Camera() :
    position_{Math::Vector3{0,0,0}},
    forward_{Math::Vector3{0,0,1}},
    up_{Math::Vector3{0,1,0}}
{
}

Camera::Camera(const Math::Vector3& position, const Math::Vector3& forward, const Math::Vector3& up) :
    position_{position},
    forward_{Math::normalize(forward)},
    up_{Math::normalize(up)}
{
}

void Camera::move(const Math::Vector3& direction, float amount)
{
    position_ = position_ + amount * direction;
}

Math::Vector3 Camera::get_position() const
{
    return position_;
}

Math::Vector3 Camera::get_left() const
{
    return Math::normalize(Math::cross(forward_, up_));
}

Math::Vector3 Camera::get_right() const
{
    return Math::normalize(Math::cross(up_, forward_));
}

Math::Vector3 Camera::get_forward() const
{
    return forward_;
}

Math::Vector3 Camera::get_up() const
{
    return up_;
}

void Camera::rotate_x(float degrees)
{
    Math::Vector3 horizontal_axis = Math::normalize(Math::cross(world_up_, forward_));

    forward_ = Math::normalize(Math::rotate(forward_, degrees, horizontal_axis));

    up_ = Math::normalize(Math::cross(forward_, horizontal_axis));
}

void Camera::rotate_y(float degrees)
{
    Math::Vector3 horizontal_axis = Math::normalize(Math::cross(world_up_, forward_));

    forward_ = Math::normalize(Math::rotate(forward_, degrees, world_up_));

    up_ = Math::normalize(Math::cross(forward_, horizontal_axis));
}
