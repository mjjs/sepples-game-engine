#include "vector2.h"
#include <ostream>

Math::Vector2 operator+(const Math::Vector2& lhs, const Math::Vector2& rhs)
{
    return Math::Vector2{lhs.x+rhs.x, lhs.y+rhs.y};
}

Math::Vector2 operator-(const Math::Vector2& lhs, const Math::Vector2& rhs)
{
    return Math::Vector2{lhs.x-rhs.x, lhs.y-rhs.y};
}

Math::Vector2 operator*(const Math::Vector2& lhs, const Math::Vector2& rhs)
{
    return Math::Vector2{lhs.x * rhs.x, lhs.y * rhs.y};
}

std::ostream& operator<<(std::ostream& os, const Math::Vector2& vec2)
{
    os << "(" << vec2.x << "," << vec2.y << ")";
    return os;
}
