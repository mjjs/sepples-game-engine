#ifndef _SGE_VECTOR_2_H
#define _SGE_VECTOR_2_H

#include <cmath>
#include <ostream>

namespace SGE {

class Vector2 {
    public:
        float x = 0;
        float y = 0;

        float angle_to(const Vector2& rhs) const;
        float length() const;
        float dot(const Vector2& rhs) const;
        Vector2 normalize();
        Vector2 normalized() const;
        float cross(const Vector2& rhs) const;
        Vector2 rotate(float degrees) const;
        Vector2 lerp(const Vector2& destination, float lerp_factor) const;
};

std::ostream& operator<<(std::ostream& os, const Vector2& vec);
Vector2 operator*(const Vector2& vector, float scalar);
Vector2 operator*(float scalar, const Vector2& vector);
Vector2 operator*(const Vector2& vector, int scalar);
Vector2 operator*(int scalar, const Vector2& vector);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
bool operator==(const Vector2& lhs, const Vector2& rhs);

} // namespace SGE

#endif
