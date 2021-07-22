#include "camera.h"
#include "matrix4.h"
#include "transform.h"
#include "vector3.h"

namespace SGE {

Matrix4 Transform::get_transformation() const
{
    const Matrix4 position = Matrix4::translation(position_);
    const Matrix4 rotation = rotation_.to_rotation_matrix();
    const Matrix4 scale = Matrix4::scale(scale_);

    return position * rotation * scale;
}

} // namespace SGE
