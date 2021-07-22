#include "sgemath.h"
#include <cmath>

namespace SGE {

float angle_to(const Vector2& vec_a, const Vector2& vec_b)
{
    return std::acos(dot(vec_a, vec_b) / (length(vec_a) * length(vec_b)));
}

float length(const Vector2& vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

float dot(const Vector2& vec_a, const Vector2& vec_b)
{
    return vec_a.x * vec_b.x + vec_a.y * vec_b.y;
}

Vector2 normalize(const Vector2& vec)
{
    const float len = length(vec);
    return Vector2{vec.x/len, vec.y/len};
}

float cross(const Vector2& vec_a, const Vector2& vec_b)
{
    return vec_a.x * vec_b.y - vec_a.y * vec_b.x;
}

Vector2 rotate(const Vector2& vec, float degrees)
{
    const float radians = to_radians(degrees);
    const float cos = std::cos(radians);
    const float sin = std::sin(radians);

    return Vector2{
        cos * vec.x - sin * vec.y,
            sin * vec.x + cos * vec.y
    };
}

Vector2 lerp(
        const Vector2& start,
        const Vector2& destination,
        const float lerp_factor
        )
{
    return start + (destination - start) * lerp_factor;
}


float angle_to(const Vector3& vec_a, const Vector3& vec_b)
{
    return std::acos(dot(vec_a, vec_b) / (length(vec_a) * length(vec_b)));
}

float length(const Vector3& vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float dot(const Vector3& vec_a, const Vector3& vec_b)
{
    return vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z;
}

Vector3 normalize(const Vector3& vec)
{
    const float len = length(vec);
    return Vector3{vec.x/len, vec.y/len, vec.z/len};
}

Vector3 cross(const Vector3& vec_a, const Vector3& vec_b)
{
    return Vector3{
        vec_a.y * vec_b.z - vec_a.z * vec_b.y,
            vec_a.z * vec_b.x - vec_a.x * vec_b.z,
            vec_a.x * vec_b.y - vec_a.y * vec_b.x
    };
}

Vector3 rotate(const Vector3& vec, float degrees, const Vector3& axis)
{
    Quaternion rotation = Quaternion{}.init_rotation(axis, degrees);
    Quaternion conjug = conjugate(rotation);

    Quaternion w = rotation * vec * conjug;

    return Vector3{w.x, w.y, w.z};
}

Vector3 lerp(
        const Vector3& start,
        const Vector3& destination,
        const float lerp_factor
        )
{
    return start + (destination - start) * lerp_factor;
}

float length(const Quaternion& q)
{
    return std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

Quaternion normalize(const Quaternion& q)
{
    const float len = length(q);
    return Quaternion{q.x/len, q.y/len, q.z/len, q.w/len};
}

Quaternion conjugate(const Quaternion& q)
{
    return Quaternion{-q.x, -q.y, -q.z, q.w};
}

float to_radians(const float degrees)
{
    return static_cast<float>(degrees * (M_PI / 180));
}

} // namespace SGE
