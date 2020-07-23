#ifndef _GE_VECTOR_2_H
#define _GE_VECTOR_2_H

#include <ostream>

namespace Math {
    struct Vector2 {
        float x;
        float y;
    };
} // namespace Math

std::ostream& operator<<(std::ostream& os, const Math::Vector2& vec2);
Math::Vector2 operator+(const Math::Vector2& lhs, const Math::Vector2& rhs);
Math::Vector2 operator-(const Math::Vector2& lhs, const Math::Vector2& rhs);
Math::Vector2 operator*(const Math::Vector2& lhs, const Math::Vector2& rhs);

#endif
