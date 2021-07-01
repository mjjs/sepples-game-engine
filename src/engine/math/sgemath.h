#ifndef _SGE_MATH_H
#define _SGE_MATH_H

#include "vector2.h"
#include "vector3.h"
#include "quaternion.h"

namespace Math {
    // Vector2
    float angle_to(const Vector2& vec_a, const Vector2& vec_b);
    float length(const Vector2& vec);
    float dot(const Vector2& vec_a, const Vector2& vec_b);
    Vector2 normalize(const Vector2& vec);
    Vector2 rotate(const Vector2& vec, float degrees);
    Vector2 lerp(const Vector2& start, const Vector2& destination, float lerp_factor);

    // Vector3
    float angle_to(const Vector3& vec_a, const Vector3& vec_b);
    float length(const Vector3& vec);
    float dot(const Vector3& vec_a, const Vector3& vec_b);
    Vector3 normalize(const Vector3& vec);
    Vector3 cross(const Vector3& vec_a, const Vector3& vec_b);
    Vector3 rotate(const Vector3& vec, float degrees, const Vector3& axis);
    Vector3 lerp(const Vector3& start, const Vector3& destination, float lerp_factor);

    // Quaternion
    float length(const Quaternion& q);
    Quaternion normalize(const Quaternion& q);
    Quaternion conjugate(const Quaternion& q);

    float to_radians(float degrees);
} // namespace Math
#endif
