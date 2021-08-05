#include "engine/core/transform.h"

#include "engine/components/camera.h"
#include "engine/math/matrix4.h"
#include "engine/math/vector3.h"

namespace SGE
{

void Transform::set_parent(Transform* transform)
{
    parent_ = transform;
}

Matrix4 Transform::get_transformation() const
{
    const Matrix4 position = Matrix4::translation(position_);
    const Matrix4 rotation = rotation_.to_rotation_matrix();
    const Matrix4 scale    = Matrix4::scale(scale_);

    // TODO: A more efficient way of handling parent changes.
    Matrix4 parent_matrix = parent_ == nullptr ? Matrix4::identity()
                                               : parent_->get_transformation();

    return parent_matrix * position * rotation * scale;
}

void Transform::set_position(const Vector3& position_vector)
{
    position_ = position_vector;
}

const Vector3& Transform::position() const
{
    return position_;
}

void Transform::set_rotation(const Quaternion& rotation)
{
    rotation_ = rotation;
}

Quaternion Transform::rotation() const
{
    return rotation_;
}

void Transform::set_scale(const Vector3& scale_vector)
{
    scale_ = scale_vector;
}

Matrix4 Transform::get_projected_transformation(const Camera& camera) const
{
    return camera.get_view_projection() * get_transformation();
}

} // namespace SGE
