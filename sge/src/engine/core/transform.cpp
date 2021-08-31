#include "engine/core/transform.h"

#include "engine/rendering/camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace SGE
{

glm::mat4 Transform::get_transformation() const
{
    return glm::translate(glm::mat4(1.0F), position_) *
           glm::mat4_cast(rotation_) * glm::scale(glm::mat4(1.0F), scale_);
}

void Transform::set_rotation(const glm::vec3& euler_angles,
                             RotationSpace relative_to)
{
    rotation_ = glm::quat{1.0F, 0.0F, 0.0F, 0.0F};
    rotate(euler_angles, relative_to);
}

void Transform::rotate(const glm::vec3& euler_angles,
                       const RotationSpace relative_to)
{
    float x_angle = glm::radians(euler_angles.x); // NOLINT
    float y_angle = glm::radians(euler_angles.y); // NOLINT
    float z_angle = glm::radians(euler_angles.z); // NOLINT

    glm::quat x_rot = glm::angleAxis(x_angle, glm::vec3{1.0F, 0.0F, 0.0F});
    glm::quat y_rot = glm::angleAxis(y_angle, glm::vec3{0.0F, 1.0F, 0.0F});
    glm::quat z_rot = glm::angleAxis(z_angle, glm::vec3{0.0F, 0.0F, 1.0F});

    if (relative_to == RotationSpace::SELF) {
        rotation_ = rotation_ * x_rot;
        rotation_ = rotation_ * y_rot;
        rotation_ = rotation_ * z_rot;
    } else {
        rotation_ = x_rot * rotation_;
        rotation_ = y_rot * rotation_;
        rotation_ = z_rot * rotation_;
    }
}

} // namespace SGE
