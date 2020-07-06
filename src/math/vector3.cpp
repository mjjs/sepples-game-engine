#include "vector3.h"
#include <ostream>

std::ostream& operator<<(std::ostream& os, const Math::Vector3& vec3)
{
    os << "(" << vec3.x << "," << vec3.y << "," << vec3.z << ")";
    return os;
}

Math::Vector3 operator+(const Math::Vector3& lhs, const Math::Vector3& rhs)
{
    return Math::Vector3{
        lhs.x+rhs.x,
            lhs.y+rhs.y,
            lhs.z+rhs.z
    };
}
