#include "engine/rendering/camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace SGE
{

Camera::Camera(const float fov_degrees, const float aspect_ratio,
               const float z_near, const float z_far)
    : z_near_{z_near}, z_far_{z_far}, fov_degrees_{fov_degrees},
      aspect_ratio_{aspect_ratio},
      projection_type_{ProjectionType::PERSPECTIVE},
      projection_{glm::perspective(fov_degrees, aspect_ratio, z_near, z_far)}
{
}

Camera::Camera(const float left, const float right, const float bottom,
               const float top, const float z_near, const float z_far)
    : z_near_{z_near}, z_far_{z_far}, left_{left}, right_{right},
      bottom_{bottom}, top_{top},
      projection_type_{ProjectionType::ORTHOGRAPHIC},
      projection_{glm::ortho(left, right, bottom, top, z_near, z_far)}
{
}

glm::mat4 Camera::get_view_projection() const
{
    return projection_ * glm::inverse(transform_.get_transformation());
}

void Camera::move(const glm::vec3& direction, float amount)
{
    transform_.set_position(transform_.position() + (direction * amount));
}

void Camera::rotate_x(float degrees)
{
    auto rot = glm::angleAxis(glm::radians(degrees), glm::vec3{1, 0, 0});
    transform_.set_rotation(transform_.rotation() * rot);
}

void Camera::rotate_y(float degrees)
{
    auto rot = glm::angleAxis(glm::radians(degrees), world_up_);
    transform_.set_rotation(rot * transform_.rotation());
}

void Camera::update_aspect_ratio(const unsigned int width,
                                 const unsigned int height)
{
    switch (projection_type_) {
    case ProjectionType::PERSPECTIVE:
        aspect_ratio_ = (float)width / (float)height;
        projection_ =
            glm::perspective(fov_degrees_, aspect_ratio_, z_near_, z_far_);
        break;

    case ProjectionType::ORTHOGRAPHIC:
        projection_ = glm::ortho(left_, static_cast<float>(width), bottom_,
                                 static_cast<float>(height), z_near_, z_far_);
        break;
    };
}

const Transform& Camera::transform() const
{
    return transform_;
}

} // namespace SGE
