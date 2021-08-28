#include "engine/core/transform.h"

#include "engine/rendering/camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace SGE
{

void Transform::set_parent(Transform* transform)
{
    parent_ = transform;
}

glm::mat4 Transform::get_transformation() const
{
    return glm::translate(glm::mat4(1.0F), position_) *
           glm::mat4_cast(rotation_) * glm::scale(glm::mat4(1.0F), scale_);
}

void Transform::set_position(const glm::vec3& position_vector)
{
    position_ = position_vector;
}

const glm::vec3& Transform::position() const
{
    return position_;
}

void Transform::set_rotation(const glm::quat& rotation)
{
    rotation_ = rotation;
}

glm::quat Transform::rotation() const
{
    return rotation_;
}

void Transform::set_scale(const glm::vec3& scale_vector)
{
    scale_ = scale_vector;
}

} // namespace SGE
