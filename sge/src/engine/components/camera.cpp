#include "camera.h"

#include "matrix4.h"
#include "vector3.h"

namespace SGE
{

Camera::Camera(const float fov_degrees, const float aspect_ratio,
               const float z_near, const float z_far)
    : projection_{
          Matrix4::perspective(fov_degrees, aspect_ratio, z_near, z_far)}
{
}

Matrix4 Camera::get_view_projection() const
{
    const Matrix4 camera_rotation = transform_.rotation().to_rotation_matrix();
    const Matrix4 camera_translation =
        Matrix4::translation(-1 * transform_.position());

    return projection_ * (camera_rotation * camera_translation);
}

void Camera::move(const Vector3& direction, float amount)
{
    transform_.set_position(transform_.position() + (direction * amount));
}

void Camera::rotate_x(float degrees)
{
    auto rotation =
        Quaternion{transform_.rotation().get_right(), degrees}.normalized();
    transform_.set_rotation(transform_.rotation() * rotation);
}

void Camera::rotate_y(float degrees)
{
    auto rotation = Quaternion{world_up_, degrees}.normalized();
    transform_.set_rotation(transform_.rotation() * rotation);
}

const Transform& Camera::transform() const
{
    return transform_;
}

} // namespace SGE
