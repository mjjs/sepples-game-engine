#include "vector3.h"
#include "quaternion.h"
#include "sgemath.h"

namespace SGE {

float Vector3::angle_to(const Vector3& vec) const
{
    return std::acos(dot(vec) / (length() * vec.length()));
}

float Vector3::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

float Vector3::dot(const Vector3& vec) const
{
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::normalize()
{
    const float len = length();
    x /= len;
    y /= len;
    z /= len;

    return *this;
}

Vector3 Vector3::normalized() const
{
    const float len = length();
    return Vector3{x/len, y/len, z/len};
}

Vector3 Vector3::cross(const Vector3& vec) const
{
    return Vector3{
        y * vec.z - z * vec.y,
        z * vec.x - x * vec.z,
        x * vec.y - y * vec.x
    };
}

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

std::ostream& operator<<(const Vector3& vector, std::ostream& os)
{
    os << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
    return os;
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3{
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z,
    };
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3{
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z,
    };
}

Vector3 operator*(const Vector3& vector, const int scalar)
{
    return Vector3{
        vector.x * static_cast<float>(scalar),
        vector.y * static_cast<float>(scalar),
        vector.z * static_cast<float>(scalar),
    };
}

Vector3 operator*(const int scalar, const Vector3& vector)
{
    return vector * scalar;
}

Vector3 operator*(const Vector3& vector, const float scalar)
{
    return Vector3{
        vector.x * scalar,
        vector.y * scalar,
        vector.z * scalar,
    };
}

Vector3 operator*(const float scalar, const Vector3& vector)
{
    return vector * scalar;
}

bool operator==(const Vector3& lhs, const Vector3& rhs)
{
    return lhs.x == rhs.x &&
        lhs.y == rhs.y &&
        lhs.z == rhs.z;
}

} // namepsace SGE
