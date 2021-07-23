#ifndef _SGE_QUATERNION_H
#define _SGE_QUATERNION_H

#include "vector3.h"
#include "matrix4.h"

namespace SGE {

class Quaternion {
    public:
        float x = 0;
        float y = 0;
        float z = 0;
        float w = 1;

        Quaternion() = default;
        Quaternion(float x, float y, float z, float w);
        Quaternion(const Vector3& axis, float angle);

        Matrix4 to_rotation_matrix() const;
        Vector3 get_forward() const;
        Vector3 get_back() const;
        Vector3 get_up() const;
        Vector3 get_down() const;
        Vector3 get_right() const;
        Vector3 get_left() const;
        float length() const;
        Quaternion normalize();
        Quaternion normalized() const;
        Quaternion conjugate() const;
};

Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator*(const Quaternion& lhs, const Vector3& rhs);
Quaternion operator*(const Vector3& lhs, const Quaternion& rhs);
Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs);

} // namespace SGE

#endif
