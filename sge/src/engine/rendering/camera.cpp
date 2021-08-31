#include "engine/rendering/camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace SGE
{

Camera::Camera(const float fov_degrees, const float aspect_ratio,
               const float z_near, const float z_far)
    : fov_degrees_{fov_degrees}, aspect_ratio_{aspect_ratio},
      perspective_z_near_{z_near}, perspective_z_far_{z_far},
      projection_type_{ProjectionType::PERSPECTIVE}
{
    recalculate_projection();
}

Camera::Camera(const float orthographic_size, const float z_near,
               const float z_far)
    : orthographic_size_{orthographic_size}, orthographic_z_near_{z_near},
      orthographic_z_far_{z_far}, projection_type_{ProjectionType::ORTHOGRAPHIC}
{
    recalculate_projection();
}

void Camera::update_aspect_ratio(const unsigned int width,
                                 const unsigned int height)
{
    aspect_ratio_ = (float)width / (float)height;
    recalculate_projection();
}

void Camera::recalculate_projection()
{
    switch (projection_type_) {
    case ProjectionType::PERSPECTIVE:
        projection_ =
            glm::perspective(glm::radians(fov_degrees_), aspect_ratio_,
                             perspective_z_near_, perspective_z_far_);
        break;

    case ProjectionType::ORTHOGRAPHIC:
        float left   = -orthographic_size_ * aspect_ratio_ * 0.5F;
        float right  = orthographic_size_ * aspect_ratio_ * 0.5F;
        float bottom = -orthographic_size_ * 0.5F;
        float top    = orthographic_size_ * 0.5F;

        projection_ = glm::ortho(left, right, bottom, top, orthographic_z_near_,
                                 orthographic_z_far_);
        break;
    };
}

} // namespace SGE
