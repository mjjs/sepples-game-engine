#include "vector3.h"
#include "quaternion.h"

Math::Quaternion operator*(const Math::Quaternion& lhs, const Math::Quaternion& rhs)
{
    return Math::Quaternion{
        lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y + lhs.w * rhs.x,
            -lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x + lhs.w * rhs.y,
            lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w + lhs.w * rhs.z,
            -lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z + lhs.w * rhs.w
    };
}

Math::Quaternion operator*(const Math::Quaternion& lhs, const Math::Vector3& rhs)
{
    return Math::Quaternion{
        -lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
            lhs.w * lhs.x + lhs.y * lhs.z- lhs.z * rhs.y,
            lhs.w * lhs.y + lhs.z * lhs.x- lhs.x * rhs.z,
            lhs.w * lhs.z + lhs.x * lhs.y- lhs.y * rhs.x
    };
}

Math::Quaternion operator+(const Math::Quaternion& lhs, const Math::Quaternion& rhs)
{
    return Math::Quaternion {
        lhs.x + rhs.x,
            lhs.y + rhs.y,
            lhs.z + rhs.z,
            lhs.w + rhs.w
    };
}
