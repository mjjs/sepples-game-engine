#include "vector2.h"
#include <cmath>
#include <ostream>

Math::Vector2::Vector2(const float x, const float y) :
    x{x},
    y{y}
{}

float Math::Vector2::angle_to(const Math::Vector2& vec2) const
{
    return std::acos(dot(vec2) / (length() * vec2.length()));
}

float Math::Vector2::getX() const
{
    return x;
}

float Math::Vector2::getY() const
{
    return y;
}

void Math::Vector2::setX(const float x)
{
    this->x = x;
}

void Math::Vector2::setY(const float y)
{
    this->y = y;
}

float Math::Vector2::length() const
{
    return std::sqrt(x * x + y * y);
}

float Math::Vector2::dot(const Math::Vector2& vec2) const
{
    return x * vec2.getX() + y * vec2.getY();
}

Math::Vector2 Math::Vector2::normalize() const
{
    const float len = length();
    return Math::Vector2(x/len, y/len);
}

Math::Vector2 Math::Vector2::rotate(float degrees) const
{
    const float radians = degrees * (static_cast<float>(M_PI)/180);
    const float cos = std::cos(radians);
    const float sin = std::sin(radians);

    return Math::Vector2(cos*x-sin*y, sin*x+cos*y);
}

Math::Vector2 operator+(const Math::Vector2& lhs, const Math::Vector2& rhs)
{
    return Math::Vector2(lhs.getX()+rhs.getX(), lhs.getY()+rhs.getY());
}

std::ostream& operator<<(std::ostream& os, const Math::Vector2& vec2)
{
    os << "(" << vec2.getX() << "," << vec2.getY() << ")";
    return os;
}
