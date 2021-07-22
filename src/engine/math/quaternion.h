#ifndef _SGE_QUATERNION_H
#define _SGE_QUATERNION_H

#include "vector3.h"
#include "matrix4.h"

namespace SGE {
namespace Math {

class Quaternion {
    public:
        float x = 0;
        float y = 0;
        float z = 0;
        float w = 1;

        inline Matrix4 to_rotation_matrix() const
        {
            return Matrix4::rotation(get_forward(), get_up(), get_right());
        }

        Quaternion init_rotation(const Vector3& axis, float angle);

        inline Vector3 get_forward() const
        {
            return Vector3{
                2.0F * (x * z - w * y),
                2.0F * (y * z + w * x),
                1.0F - 2.0F * (x * x + y * y),
            };
        }

        inline Vector3 get_back() const
        {
            return Vector3{
                -2.0F * (x * z - w * y),
                -2.0F * (y * z + w * x),
                -(1.0F - 2.0F * (x * x + y * y)),
            };
        }

        inline Vector3 get_up() const
        {
            return Vector3{
                2.0F * (x * y + w * z),
                1.0F - 2.0F * (x * x + z * z),
                2.0F * (y * z - w * x),
            };
        }

        inline Vector3 get_down() const
        {
            return Vector3{
                -2.0F * (x * y + w * z),
                -(1.0F - 2.0F * (x * x + z * z)),
                -2.0F * (y * z - w * x),
            };
        }

        inline Vector3 get_right() const
        {
            return Vector3{
                1.0F - 2.0F * (y * y + z * z),
                2.0F * (x * y - w * z),
                2.0F * (x * z + w * y),
            };
        }

        inline Vector3 get_left() const
        {
            return Vector3{
                -(1.0F - 2.0F * (y * y + z * z)),
                -2.0F * (x * y - w * z),
                -2.0F * (x * z + w * y),
            };
        }

};

inline Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
{
    return Math::Quaternion{
        lhs.x * rhs.w + lhs.w * rhs.x + lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.y * rhs.w + lhs.w * rhs.y + lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.z * rhs.w + lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x,
            lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z
    };
}

inline Quaternion operator*(const Quaternion& lhs, const Vector3& rhs)
{
    return Math::Quaternion{
        lhs.w * rhs.x + lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.w * rhs.y + lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x,
            -lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z
    };
}

inline Quaternion operator*(const Vector3& lhs, const Quaternion& rhs)
{
    return rhs * lhs;
}

inline Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs)
{
    return Math::Quaternion {
        lhs.x + rhs.x,
            lhs.y + rhs.y,
            lhs.z + rhs.z,
            lhs.w + rhs.w
    };
}

} // namespace Math
} // namespace SGE

#endif
