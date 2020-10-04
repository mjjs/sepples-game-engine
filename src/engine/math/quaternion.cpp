#include "vector3.h"
#include "quaternion.h"

Math::Quaternion operator*(const Math::Quaternion& lhs, const Math::Quaternion& rhs)
{
    return Math::Quaternion{
        lhs.x * rhs.w + lhs.w * rhs.x + lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.y * rhs.w + lhs.w * rhs.y + lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.z * rhs.w + lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x,
            lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z
    };
}

Math::Quaternion operator*(const Math::Quaternion& lhs, const Math::Vector3& rhs)
{
    return Math::Quaternion{
        lhs.w * rhs.x + lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.w * rhs.y + lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x,
            -lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z
    };
    //return Math::Quaternion{
    //    -lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
    //        lhs.w * rhs.x + lhs.y * rhs.z - lhs.z * rhs.y,
    //        lhs.w * rhs.y + lhs.z * rhs.x - lhs.x * rhs.z,
    //        lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x
    //};
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
