#include "vector3.h"
#include "matrix4.h"
#include "quaternion.h"

#include <cmath>

namespace SGE {

Quaternion::Quaternion(const float x, const float y, const float z, const float w)
    : x{x}, y{y}, z{z}, w{w}
{
}

Quaternion::Quaternion(const Vector3& axis, float angle)
{
    float sin_half_angle = std::sin(angle / 2);
    float cos_half_angle = std::cos(angle / 2);

    x = axis.x * sin_half_angle;
    y = axis.y * sin_half_angle;
    z = axis.z * sin_half_angle;
    w = cos_half_angle;
}

} // namespace SGE
