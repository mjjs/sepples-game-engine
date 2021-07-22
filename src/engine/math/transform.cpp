#include "camera.h"
#include "matrix4.h"
#include "transform.h"
#include "vector3.h"

namespace SGE {

Math::Matrix4 Math::Transform::get_transformation() const
{
    const Math::Matrix4 position = Math::Matrix4::translation(position_);
    const Math::Matrix4 rotation = rotation_.to_rotation_matrix();
    const Math::Matrix4 scale = Math::Matrix4::scale(scale_);

    return position * rotation * scale;
}

} // namespace SGE
