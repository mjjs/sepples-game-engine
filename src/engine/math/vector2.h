#ifndef _SGE_VECTOR_2_H
#define _SGE_VECTOR_2_H

#include <ostream>

namespace SGE {
namespace Math {

struct Vector2 {
    float x = 0;
    float y = 0;
};

std::ostream& operator<<(std::ostream& os, const Vector2& vec2);
Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(int scalar, const Vector2& vector);
Vector2 operator*(float scalar, const Vector2& vector);
Vector2 operator*(const Vector2& vector, int scalar);
Vector2 operator*(const Vector2& vector, float scalar);
bool operator==(const Vector2& lhs, const Vector2& rhs);

} // namespace Math
} // namespace SGE


#endif
