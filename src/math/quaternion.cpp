#include "vector3.h"
#include "quaternion.h"
#include <cmath>

Math::Quaternion::Quaternion(const float x, const float y, const float z,
        const float w) :
    x{x},
    y{y},
    z{z},
    w{w}
{}

float Math::Quaternion::length() const
{
    return std::sqrt(x*x + y*y + z*z + w*w);
}

Math::Quaternion Math::Quaternion::normalize() const
{
    const float len = length();
    return Math::Quaternion{x/len, y/len, z/len, w/len};
}

Math::Quaternion Math::Quaternion::conjugate() const
{
    return Math::Quaternion{-x, -y, -z, w};
}

Math::Quaternion operator*(const Math::Quaternion& lhs, const Math::Quaternion& rhs)
{
    return Math::Quaternion{
        lhs.get_x() * rhs.get_w() + lhs.get_y() * rhs.get_z() - lhs.get_z() * rhs.get_y() + lhs.get_w() * rhs.get_x(),
            -lhs.get_x() * rhs.get_z() + lhs.get_y() * rhs.get_w() + lhs.get_z() * rhs.get_x() + lhs.get_w() * rhs.get_y(),
            lhs.get_x() * rhs.get_y() - lhs.get_y() * rhs.get_x() + lhs.get_z() * rhs.get_w() + lhs.get_w() * rhs.get_z(),
            -lhs.get_x() * rhs.get_x() - lhs.get_y() * rhs.get_y() - lhs.get_z() * rhs.get_z() + lhs.get_w() * rhs.get_w()
    };
}

Math::Quaternion operator*(const Math::Quaternion& lhs, const Math::Vector3& rhs)
{
    return Math::Quaternion{
        -lhs.get_x() * rhs.get_x() - lhs.get_y() * rhs.get_y() - lhs.get_z() * rhs.get_z(),
            lhs.get_w() * lhs.get_x() + lhs.get_y() * lhs.get_z()- lhs.get_z() * rhs.get_y(),
            lhs.get_w() * lhs.get_y() + lhs.get_z() * lhs.get_x()- lhs.get_x() * rhs.get_z(),
            lhs.get_w() * lhs.get_z() + lhs.get_x() * lhs.get_y()- lhs.get_y() * rhs.get_x()
    };
}

Math::Quaternion operator+(const Math::Quaternion& lhs, const Math::Quaternion& rhs)
{
    return Math::Quaternion {
        lhs.get_x() + rhs.get_x(),
            lhs.get_y() + rhs.get_y(),
            lhs.get_z() + rhs.get_z(),
            lhs.get_w() + rhs.get_w()
    };
}

float Math::Quaternion::get_x() const
{
    return x;
}

float Math::Quaternion::get_y() const
{
    return y;
}

float Math::Quaternion::get_z() const
{
    return z;
}

float Math::Quaternion::get_w() const
{
    return w;
}

void Math::Quaternion::set_x(const float x)
{
    this->x=x;
}

void Math::Quaternion::set_y(const float y)
{
    this->y=y;
}

void Math::Quaternion::set_z(const float z)
{
    this->z=z;
}

void Math::Quaternion::set_w(const float w)
{
    this->w=w;
}
