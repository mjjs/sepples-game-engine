#ifndef _SGE_VECTOR_3_H
#define _SGE_VECTOR_3_H

#include <ostream>

namespace SGE {
namespace Math {

struct Vector3 {
    float x = 0;
    float y = 0;
    float z = 0;
};

std::ostream& operator<<(std::ostream& os, const Vector3& vec3);
Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
Vector3 operator*(int scalar, const Vector3& vector);
Vector3 operator*(float scalar, const Vector3& vector);
Vector3 operator*(const Vector3& vector, int scalar);
Vector3 operator*(const Vector3& vector, float scalar);
bool operator==(const Vector3& lhs, const Vector3& rhs);

} // namespace Math
} // namespace SGE


#endif
