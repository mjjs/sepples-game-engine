#ifndef _GE_VECTOR_3_H
#define _GE_VECTOR_3_H

#include <ostream>

namespace Math {
    struct Vector3 {
        float x = 0;
        float y = 0;
        float z = 0;
    };
} // namespace Math

std::ostream& operator<<(std::ostream& os, const Math::Vector3& vec3);
Math::Vector3 operator+(const Math::Vector3& lhs, const Math::Vector3& rhs);
Math::Vector3 operator*(int scalar, const Math::Vector3& vector);
Math::Vector3 operator*(float scalar, const Math::Vector3& vector);

#endif
