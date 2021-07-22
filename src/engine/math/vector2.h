#ifndef _SGE_VECTOR_2_H
#define _SGE_VECTOR_2_H

#include <cmath>
#include <ostream>

namespace SGE {

class Vector2 {
    public:
        float x = 0;
        float y = 0;

        inline float angle_to(const Vector2& rhs) const
        {
            return std::acos(dot(rhs) / (length() * rhs.length()));
        }

        inline float length() const
        {
            return std::sqrt(x * x + y * y);
        }

        inline float dot(const Vector2& rhs) const
        {
            return x * rhs.x + y * rhs.y;
        }

        inline Vector2 normalize()
        {
            const float len = length();

            x /= len;
            y /= len;

            return *this;
        }

        inline Vector2 normalized() const
        {
            const float len = length();
            return Vector2{x/len, y/len};
        }

        inline float cross(const Vector2& rhs) const
        {
            return x * rhs.y - y * rhs.x;
        }

        Vector2 rotate(float degrees) const;
        Vector2 lerp(const Vector2& destination, float lerp_factor) const;
};

inline std::ostream& operator<<(std::ostream& os, const Vector2& vec)
{
    os << "(" << vec.x << "," << vec.y << ")";
    return os;
}

inline Vector2 operator*(const Vector2& vector, const float scalar)
{
    return Vector2{
        vector.x * scalar,
        vector.y * scalar,
    };
}

inline Vector2 operator*(const float scalar, const Vector2& vector)
{
    return vector * scalar;
}

inline Vector2 operator*(const Vector2& vector, const int scalar)
{
    return vector * static_cast<float>(scalar);
}

inline Vector2 operator*(const int scalar, const Vector2& vector)
{
    return vector * scalar;
}

inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2{
        lhs.x - rhs.x,
        lhs.y - rhs.y,
    };
}

inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2{
        lhs.x + rhs.x,
        lhs.y + rhs.y,
    };
}

inline bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

} // namespace SGE


#endif
