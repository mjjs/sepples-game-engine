#include "transform.h"
#include "matrix4.h"
#include "vector3.h"

#include <iostream>

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

    return translation * scale * rotation;
}

Math::Matrix4 Math::Transform::get_projected_transformation() const
{
    const Math::Matrix4 projection_matrix = Math::Matrix4::projection(fov_, width_,
            height_, z_near_, z_far_);

    return projection_matrix * get_transformation();
}

void Math::Transform::set_projection(float fov, float width, float height, float z_near, float z_far)
{
    fov_ = fov;
    width_ = width;
    height_ = height;
    z_near_ = z_near;
    z_far_ = z_far;
}
