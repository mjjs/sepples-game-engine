#ifndef _GE_VECTOR_3_H
#define _GE_VECTOR_3_H

#include <ostream>

namespace Math {
    struct Vector3 {
        float x;
        float y;
        float z;
    };
} // namespace Math

std::ostream& operator<<(std::ostream& os, const Math::Vector3& vec3);
Math::Vector3 operator+(const Math::Vector3& lhs, const Math::Vector3& rhs);

#endif
