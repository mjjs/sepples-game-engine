#include "vector3.h"
#include <ostream>

namespace SGE {

std::ostream& operator<<(std::ostream& os, const Vector3& vec3)
{
    os << "(" << vec3.x << "," << vec3.y << "," << vec3.z << ")";
    return os;
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3{
        lhs.x+rhs.x,
            lhs.y+rhs.y,
            lhs.z+rhs.z
    };
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3{
        lhs.x-rhs.x,
            lhs.y-rhs.y,
            lhs.z-rhs.z
    };
}

Vector3 operator*(int scalar, const Vector3& vector)
{
    return static_cast<float>(scalar) * vector;
}

Vector3 operator*(float scalar, const Vector3& vector)
{
    return Vector3{vector.x * scalar, vector.y * scalar, vector.z * scalar};
}

Vector3 operator*(const Vector3& vector, const int scalar)
{
    return vector * static_cast<float>(scalar);
}

Vector3 operator*(const Vector3& vector, const float scalar)
{
    return Vector3{vector.x * scalar, vector.y * scalar, vector.z * scalar};
}

bool operator==(const Vector3& lhs, const Vector3& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

} // namespace SGE
