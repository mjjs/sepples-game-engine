#include "sgemath.h"
#include <cmath>

float Math::angle_to(const Math::Vector2& vec_a, const Math::Vector2& vec_b)
{
    return std::acos(Math::dot(vec_a, vec_b) / (Math::length(vec_a) * Math::length(vec_b)));
}

float Math::length(const Math::Vector2& vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

float Math::dot(const Math::Vector2& vec_a, const Math::Vector2& vec_b)
{
    return vec_a.x * vec_b.x + vec_a.y * vec_b.y;
}

Math::Vector2 Math::normalize(const Math::Vector2& vec)
{
    const float length = Math::length(vec);
    return Math::Vector2{vec.x/length, vec.y/length};
}

float Math::cross(const Math::Vector2& vec_a, const Math::Vector2& vec_b)
{
    return vec_a.x * vec_b.y - vec_a.y * vec_b.x;
}

Math::Vector2 Math::rotate(const Math::Vector2& vec, float degrees)
{
    const float radians = Math::to_radians(degrees);
    const float cos = std::cos(radians);
    const float sin = std::sin(radians);

    return Math::Vector2{
        cos * vec.x - sin * vec.y,
            sin * vec.x + cos * vec.y
    };
}

Math::Vector2 Math::lerp(
        const Math::Vector2& start,
        const Math::Vector2& destination,
        const float lerp_factor
        )
{
    return start + (destination - start) * lerp_factor;
}


float Math::angle_to(const Math::Vector3& vec_a, const Math::Vector3& vec_b)
{
    return std::acos(Math::dot(vec_a, vec_b) / (Math::length(vec_a) * Math::length(vec_b)));
}

float Math::length(const Math::Vector3& vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float Math::dot(const Math::Vector3& vec_a, const Math::Vector3& vec_b)
{
    return vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z;
}

Math::Vector3 Math::normalize(const Math::Vector3& vec)
{
    const float length = Math::length(vec);
    return Math::Vector3{vec.x/length, vec.y/length, vec.z/length};
}

Math::Vector3 Math::cross(const Math::Vector3& vec_a, const Math::Vector3& vec_b)
{
    return Math::Vector3{
        vec_a.y * vec_b.z - vec_a.z * vec_b.y,
            vec_a.z * vec_b.x - vec_a.x * vec_b.z,
            vec_a.x * vec_b.y - vec_a.y * vec_b.x
    };
}

Math::Vector3 Math::rotate(const Math::Vector3& vec, float degrees, const Vector3& axis)
{
    float sin_half_angle = std::sin(Math::to_radians(degrees / 2));
    float cos_half_angle = std::cos(Math::to_radians(degrees / 2));

    Math::Quaternion rotation{
        axis.x * sin_half_angle,
            axis.y * sin_half_angle,
            axis.z * sin_half_angle,
            cos_half_angle
    };

    Math::Quaternion conjugate = Math::conjugate(rotation);

    Math::Quaternion rotated = rotation * vec * conjugate;

    return Math::Vector3{
        rotated.x,
            rotated.y,
            rotated.z
    };
}

Math::Vector3 Math::lerp(
        const Math::Vector3& start,
        const Math::Vector3& destination,
        const float lerp_factor
        )
{
    return start + (destination - start) * lerp_factor;
}

float Math::length(const Math::Quaternion& q)
{
    return std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

Math::Quaternion Math::normalize(const Math::Quaternion& q)
{
    const float length = Math::length(q);
    return Math::Quaternion{q.x/length, q.y/length, q.z/length, q.w/length};
}

Math::Quaternion Math::conjugate(const Math::Quaternion& q)
{
    return Math::Quaternion{-q.x, -q.y, -q.z, q.w};
}

float Math::to_radians(const float degrees)
{
    return static_cast<float>(degrees * (M_PI / 180));
}
