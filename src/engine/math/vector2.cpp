#include "vector2.h"
#include "sgemath.h"

namespace SGE {

float Vector2::angle_to(const Vector2& rhs) const
{
    return std::acos(dot(rhs) / (length() * rhs.length()));
}

float Vector2::length() const
{
    return std::sqrt(x * x + y * y);
}

float Vector2::dot(const Vector2& rhs) const
{
    return x * rhs.x + y * rhs.y;
}

Vector2 Vector2::normalize()
{
    const float len = length();

    x /= len;
    y /= len;

    return *this;
}

Vector2 Vector2::normalized() const
{
    const float len = length();
    return Vector2{x/len, y/len};
}

float Vector2::cross(const Vector2& rhs) const
{
    return x * rhs.y - y * rhs.x;
}

Vector2 Vector2::Vector2::lerp(const Vector2& destination, const float lerp_factor) const
{
    return *this + (destination - *this) * lerp_factor;
}

Vector2 Vector2::rotate(float degrees) const
{
    const float radians = to_radians(degrees);
    const float cos = std::cos(radians);
    const float sin = std::sin(radians);

    return Vector2{
        cos * x - sin * y,
        sin * x + cos * y
    };
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec)
{
    os << "(" << vec.x << "," << vec.y << ")";
    return os;
}

Vector2 operator*(const Vector2& vector, const float scalar)
{
    return Vector2{
        vector.x * scalar,
        vector.y * scalar,
    };
}

Vector2 operator*(const float scalar, const Vector2& vector)
{
    return vector * scalar;
}

Vector2 operator*(const Vector2& vector, const int scalar)
{
    return vector * static_cast<float>(scalar);
}

Vector2 operator*(const int scalar, const Vector2& vector)
{
    return vector * scalar;
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2{
        lhs.x - rhs.x,
        lhs.y - rhs.y,
    };
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2{
        lhs.x + rhs.x,
        lhs.y + rhs.y,
    };
}

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

} // namespace SGE
