#ifndef _VECTOR_3_H
#define _VECTOR_3_H

#include <ostream>

namespace Math {
class Vector3 {
    private:
        float x;
        float y;
        float z;

    public:
        Vector3() = default;
        Vector3(float x, float y, float z);

        float angle_to(const Vector3& vec3) const;
        float length() const;
        float dot(const Vector3& vec3) const;
        Vector3 normalize() const;
        Vector3 cross(const Vector3& vec3) const;

        float get_x() const;
        float get_y() const;
        float get_z() const;

        void set_x(float x);
        void set_y(float y);
        void set_z(float z);
};
} // namespace Math

std::ostream& operator<<(std::ostream& os, const Math::Vector3& vec3);
Math::Vector3 operator+(const Math::Vector3& lhs, const Math::Vector3& rhs);

#endif
