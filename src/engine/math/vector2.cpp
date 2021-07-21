#include "vector2.h"
#include <ostream>

namespace SGE {

std::ostream& Math::operator<<(std::ostream& os, const Math::Vector2& vec2)
{
    os << "(" << vec2.x << "," << vec2.y << ")";
    return os;
}

Math::Vector2 Math::operator+(const Math::Vector2& lhs, const Math::Vector2& rhs)
{
    return Math::Vector2{lhs.x+rhs.x, lhs.y+rhs.y};
}

Math::Vector2 Math::operator-(const Math::Vector2& lhs, const Math::Vector2& rhs)
{
    return Math::Vector2{lhs.x-rhs.x, lhs.y-rhs.y};
}

Math::Vector2 Math::operator*(int scalar, const Math::Vector2& vector)
{
    return static_cast<float>(scalar) * vector;
}

Math::Vector2 Math::operator*(float scalar, const Math::Vector2& vector)
{
    return Math::Vector2{vector.x * scalar, vector.y * scalar};
}

Math::Vector2 Math::operator*(const Math::Vector2& vector, const int scalar)
{
    return vector * static_cast<float>(scalar);
}

Math::Vector2 Math::operator*(const Math::Vector2& vector, const float scalar)
{
    return Math::Vector2{vector.x * scalar, vector.y * scalar};
}

bool Math::operator==(const Math::Vector2& lhs, const Math::Vector2& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

} // namespace SGE
