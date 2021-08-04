#ifndef _SGE_VECTOR_3_H
#define _SGE_VECTOR_3_H

#include <cmath>
#include <ostream>

namespace SGE
{

class Quaternion;

class Vector3
{
  public:
    float x = 0;
    float y = 0;
    float z = 0;

    float angle_to(const Vector3& vec) const;
    float length() const;
    float dot(const Vector3& vec) const;
    Vector3 normalize();
    Vector3 normalized() const;
    Vector3 cross(const Vector3& vec) const;
    Vector3 lerp(const Vector3& destination, float lerp_factor) const;
    Vector3 rotate(float radians, const Vector3& axis) const;
    Vector3 rotate(const Quaternion& quaternion) const;
};

std::ostream& operator<<(const Vector3& vector, std::ostream& os);
Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
Vector3 operator*(const Vector3& vector, int scalar);
Vector3 operator*(int scalar, const Vector3& vector);
Vector3 operator*(const Vector3& vector, float scalar);
Vector3 operator*(float scalar, const Vector3& vector);
bool operator==(const Vector3& lhs, const Vector3& rhs);

} // namespace SGE

#endif
