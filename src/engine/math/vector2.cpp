#include "vector2.h"
#include <ostream>

namespace SGE {

std::ostream& operator<<(std::ostream& os, const Vector2& vec2)
{
    os << "(" << vec2.x << "," << vec2.y << ")";
    return os;
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2{lhs.x+rhs.x, lhs.y+rhs.y};
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2{lhs.x-rhs.x, lhs.y-rhs.y};
}

Vector2 operator*(int scalar, const Vector2& vector)
{
    return static_cast<float>(scalar) * vector;
}

Vector2 operator*(float scalar, const Vector2& vector)
{
    return Vector2{vector.x * scalar, vector.y * scalar};
}

Vector2 operator*(const Vector2& vector, const int scalar)
{
    return vector * static_cast<float>(scalar);
}

Vector2 operator*(const Vector2& vector, const float scalar)
{
    return Vector2{vector.x * scalar, vector.y * scalar};
}

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

} // namespace SGE
