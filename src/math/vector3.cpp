#include "vector3.h"
#include <cmath>
#include <ostream>

Math::Vector3::Vector3(const float x, const float y, const float z) :
    x{x},
    y{y},
    z{z}
{}

float Math::Vector3::angle_to(const Math::Vector3& vec3) const
{
    return std::acos(dot(vec3) / (length() * vec3.length()));
}

float Math::Vector3::length() const
{
    return std::sqrt(x*x+y*y+z*z);
}

float Math::Vector3::dot(const Vector3& vec3) const
{
    return x*vec3.get_x()+y*vec3.get_y()+z*vec3.get_z();
}

Math::Vector3 Math::Vector3::normalize() const
{
    const float len = length();

    return Vector3(x / len, y / len, z / len);
}

Math::Vector3 Math::Vector3::cross(const Math::Vector3& vec3) const
{
    return Vector3(
            y*vec3.get_z() - z*vec3.get_y(),
            z*vec3.get_x() - x*vec3.get_z(),
            x*vec3.get_y() - y*vec3.get_x()
            );
}

float Math::Vector3::get_x() const
{
    return x;
}

float Math::Vector3::get_y() const
{
    return y;
}

float Math::Vector3::get_z() const
{
    return z;
}

void Math::Vector3::set_x(const float new_x)
{
    x = new_x;
}

void Math::Vector3::set_y(const float new_y)
{
    y = new_y;
}

void Math::Vector3::set_z(const float new_z)
{
    z = new_z;
}

std::ostream& operator<<(std::ostream& os, const Math::Vector3& vec3)
{
    os << "(" << vec3.get_x() << "," << vec3.get_y() << "," << vec3.get_z() << ")";
    return os;
}

Math::Vector3 operator+(const Math::Vector3& lhs, const Math::Vector3& rhs)
{
    return Math::Vector3(
            lhs.get_x()+rhs.get_x(),
            lhs.get_y()+rhs.get_y(),
            lhs.get_z()+rhs.get_z()
            );
}
