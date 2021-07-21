#ifndef _SGE_QUATERNION_H
#define _SGE_QUATERNION_H

#include "vector3.h"

namespace SGE {
namespace Math {

struct Quaternion {
    float x;
    float y;
    float z;
    float w;
};

Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator*(const Quaternion& lhs, const Vector3& rhs);
Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs);

} // namespace Math
} // namespace SGE

#endif
