#ifndef _SGE_VECTOR_3_H
#define _SGE_VECTOR_3_H

#include <cmath>
#include <ostream>

namespace SGE {

class Vector3 {
    public:
        float x = 0;
        float y = 0;
        float z = 0;

        inline float angle_to(const Vector3& vec) const
        {
            return std::acos(dot(vec) / (length() * vec.length()));
        }

        inline float length() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        inline float dot(const Vector3& vec) const
        {
            return x * vec.x + y * vec.y + z * vec.z;
        }

        inline Vector3 normalize()
        {
            const float len = length();
            x /= len;
            y /= len;
            z /= len;

            return *this;
        }

        inline Vector3 normalized() const
        {
            const float len = length();
            return Vector3{x/len, y/len, z/len};
        }

        inline Vector3 cross(const Vector3& vec) const
        {
            return Vector3{
                y * vec.z - z * vec.y,
                z * vec.x - x * vec.z,
                x * vec.y - y * vec.x
            };
        }

        Vector3 lerp(const Vector3& destination, float lerp_factor) const;

        Vector3 rotate(float radians, const Vector3& axis) const;
};


inline std::ostream& operator<<(const Vector3& vector, std::ostream& os)
{
    os << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
    return os;
}

inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3{
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z,
    };
}

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3{
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z,
    };
}

inline Vector3 operator*(const Vector3& vector, const int scalar)
{
    return Vector3{
        vector.x * static_cast<float>(scalar),
        vector.y * static_cast<float>(scalar),
        vector.z * static_cast<float>(scalar),
    };
}

inline Vector3 operator*(const int scalar, const Vector3& vector)
{
    return vector * scalar;
}

inline Vector3 operator*(const Vector3& vector, const float scalar)
{
    return Vector3{
        vector.x * scalar,
        vector.y * scalar,
        vector.z * scalar,
    };
}

inline Vector3 operator*(const float scalar, const Vector3& vector)
{
    return vector * scalar;
}

inline bool operator==(const Vector3& lhs, const Vector3& rhs)
{
    return lhs.x == rhs.x &&
        lhs.y == rhs.y &&
        lhs.z == rhs.z;
}

} // namespace SGE


#endif
