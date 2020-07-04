#ifndef _VECTOR_2_H
#define _VECTOR_2_H

#include <ostream>

namespace Math {
class Vector2 {
    private:
        float x;
        float y;

    public:
        Vector2() = default;
        Vector2(float x, float y);
        float getX() const;
        float getY() const;
        void setX(float x);
        void setY(float y);

        float angle_to(const Vector2& vec2) const;
        float length() const;
        float dot(const Vector2& vec2) const;
        Vector2 normalize() const;
        Vector2 rotate(float degrees) const;
};
} // namespace Math

std::ostream& operator<<(std::ostream& os, const Math::Vector2& vec2);
Math::Vector2 operator+(const Math::Vector2& lhs, const Math::Vector2& rhs);

#endif
