#ifndef _QUATERNION_H
#define _QUATERNION_H
#include "vector3.h"

namespace Math {
class Quaternion {
    private:
        float x;
        float y;
        float z;
        float w;

    public:
        Quaternion() = default;
        Quaternion(float x, float y, float z, float w);

        void set_x(float x);
        void set_y(float y);
        void set_z(float z);
        void set_w(float w);

        float get_x() const;
        float get_y() const;
        float get_z() const;
        float get_w() const;

        float length() const;
        Quaternion normalize() const;
        Quaternion conjugate() const;
};
} // namespace Math

Math::Quaternion operator*(const Math::Quaternion& lhs, const Math::Quaternion& rhs);
Math::Quaternion operator*(const Math::Quaternion& lhs, const Math::Vector3& rhs);
Math::Quaternion operator+(const Math::Quaternion& lhs, const Math::Quaternion& rhs);
#endif
