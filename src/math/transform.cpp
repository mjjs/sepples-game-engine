#include "transform.h"
#include "matrix4.h"
#include "vector3.h"

void Math::Transform::set_translation(const Math::Vector3& translation_vector)
{
    translation_ = translation_vector;
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
    const Math::Matrix4 translation = Math::Matrix4::translation(translation_);
    const Math::Matrix4 rotation = Math::Matrix4::rotation(rotation_);
    const Math::Matrix4 scale = Math::Matrix4::scale(scale_);

    return scale * rotation * translation;
}
