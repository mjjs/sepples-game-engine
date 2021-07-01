#include "camera.h"
#include "matrix4.h"
#include "transform.h"
#include "vector3.h"

#include <iostream>

void Math::Transform::set_position(const Math::Vector3& position_vector)
{
    position_ = position_vector;
}

void Math::Transform::set_rotation(const Math::Vector3& rotation_vector)
{
    rotation_ = rotation_vector;
}

void Math::Transform::set_scale(const Math::Vector3& scale_vector)
{
    scale_ = scale_vector;
}

Math::Matrix4 Math::Transform::get_transformation() const
{
    const Math::Matrix4 position = Math::Matrix4::translation(position_);
    const Math::Matrix4 rotation = Math::Matrix4::rotation(rotation_);
    const Math::Matrix4 scale = Math::Matrix4::scale(scale_);

    return position * scale * rotation;
}

Math::Matrix4 Math::Transform::get_projected_transformation(const Camera& camera) const
{
    return camera.get_view_projection() * get_transformation();
}
