#include "vector3.h"
#include "quaternion.h"
#include "sgemath.h"

namespace SGE {

    Vector3 Vector3::rotate(const Quaternion& quaternion) const
    {
        Quaternion w = quaternion * *this * quaternion.conjugate();

        return Vector3{w.x, w.y, w.z};
    }

    Vector3 Vector3::rotate(float radians, const Vector3& axis) const
    {
        return rotate(Quaternion{axis, radians});
    }

    Vector3 Vector3::lerp(const Vector3& destination, float lerp_factor) const
    {
        return *this + (destination - *this) * lerp_factor;
    }

} // namepsace SGE
