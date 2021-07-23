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

Matrix4 Quaternion::to_rotation_matrix() const
{
    const Vector3 forward{
        2.0F * (x * z - w * y),
        2.0F * (y * z + w * x),
        1.0F - 2.0F * (x * x + y * y),
    };

    const Vector3 up{
        2.0F * (x * y + w * z),
        1.0F - 2.0F * (x * x + z * z),
        2.0F * (y * z - w * x),
    };

    const Vector3 right{
        1.0F - 2.0F * (y * y + z * z),
        2.0F * (x * y - w * z),
        2.0F * (x * z + w * y),
    };

    return Matrix4::rotation(forward, up, right);
}

Vector3 Quaternion::get_forward() const
{
    return Vector3{0, 0, 1}.rotate(*this);
}

Vector3 Quaternion::get_back() const
{
    return Vector3{0, 0, -1}.rotate(*this);
}

Vector3 Quaternion::get_up() const
{
    return Vector3{0, 1, 0}.rotate(*this);
}

Vector3 Quaternion::get_down() const
{
    return Vector3{0, -1, 0}.rotate(*this);
}

Vector3 Quaternion::get_right() const
{
    return Vector3{0, 0, 1}.rotate(*this);
}

Vector3 Quaternion::get_left() const
{
    return Vector3{0, 0, -1}.rotate(*this);
}

float Quaternion::length() const
{
    return std::sqrt(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::normalize()
{
    const float len = length();
    x /= len;
    y /= len;
    z /= len;
    w /= len;

    return *this;
}

Quaternion Quaternion::normalized() const
{
    const float len = length();
    return Quaternion{x/len, y/len, z/len, w/len};
}

Quaternion Quaternion::conjugate() const
{
    return Quaternion{-x, -y, -z, w};
}

Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
{
    return Quaternion{
        lhs.x * rhs.w + lhs.w * rhs.x + lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.y * rhs.w + lhs.w * rhs.y + lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.z * rhs.w + lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x,
        lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z
    };
}

Quaternion operator*(const Quaternion& lhs, const Vector3& rhs)
{
    return Quaternion{
        lhs.w * rhs.x + lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.w * rhs.y + lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x,
        -lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z
    };
}

Quaternion operator*(const Vector3& lhs, const Quaternion& rhs)
{
    return rhs * lhs;
}

Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs)
{
    return Quaternion {
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z,
        lhs.w + rhs.w
    };
}

} // namespace SGE
