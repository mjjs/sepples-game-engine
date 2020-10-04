#ifndef _GE_QUATERNION_H
#define _GE_QUATERNION_H
#include "vector3.h"

namespace Math {
    struct Quaternion {
        float x;
        float y;
        float z;
        float w;
    };
} // namespace Math

Math::Quaternion operator*(const Math::Quaternion& lhs, const Math::Quaternion& rhs);
Math::Quaternion operator*(const Math::Quaternion& lhs, const Math::Vector3& rhs);
Math::Quaternion operator+(const Math::Quaternion& lhs, const Math::Quaternion& rhs);
#endif
