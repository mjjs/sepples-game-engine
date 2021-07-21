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
    position_{Math::Vector3{0,0,0}},
    forward_{Math::Vector3{0,0,1}},
    up_{Math::Vector3{0,1,0}},
    projection_{Math::Matrix4::perspective(fov_radians, aspect_ratio, z_near, z_far)}
{
}

Math::Matrix4 Camera::get_view_projection() const
{
    const Math::Matrix4 camera_rotation = Math::Matrix4::camera(forward_, up_);
    const Math::Matrix4 camera_translation = Math::Matrix4::translation(-1 * position_);

    return projection_ * camera_rotation * camera_translation;
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

} // namespace SGE
