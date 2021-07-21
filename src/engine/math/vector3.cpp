#include "vector3.h"
#include <ostream>

namespace SGE {

std::ostream& Math::operator<<(std::ostream& os, const Math::Vector3& vec3)
{
    os << "(" << vec3.x << "," << vec3.y << "," << vec3.z << ")";
    return os;
}

Math::Vector3 Math::operator+(const Math::Vector3& lhs, const Math::Vector3& rhs)
{
    return Math::Vector3{
        lhs.x+rhs.x,
            lhs.y+rhs.y,
            lhs.z+rhs.z
    };
}

Math::Vector3 Math::operator-(const Math::Vector3& lhs, const Math::Vector3& rhs)
{
    return Math::Vector3{
        lhs.x-rhs.x,
            lhs.y-rhs.y,
            lhs.z-rhs.z
    };
}

Math::Vector3 Math::operator*(int scalar, const Math::Vector3& vector)
{
    return static_cast<float>(scalar) * vector;
}

Math::Vector3 Math::operator*(float scalar, const Math::Vector3& vector)
{
    return Math::Vector3{vector.x * scalar, vector.y * scalar, vector.z * scalar};
}

Math::Vector3 Math::operator*(const Math::Vector3& vector, const int scalar)
{
    return vector * static_cast<float>(scalar);
}

Math::Vector3 Math::operator*(const Math::Vector3& vector, const float scalar)
{
    return Math::Vector3{vector.x * scalar, vector.y * scalar, vector.z * scalar};
}

bool Math::operator==(const Math::Vector3& lhs, const Math::Vector3& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

} // namespace SGE
