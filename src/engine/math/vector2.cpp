#include "vector2.h"
#include "sgemath.h"

namespace SGE {

Vector2 Vector2::lerp(const Vector2& destination, const float lerp_factor) const
{
    return *this + (destination - *this) * lerp_factor;
}

Vector2 Vector2::rotate(float degrees) const
{
    const float radians = to_radians(degrees);
    const float cos = std::cos(radians);
    const float sin = std::sin(radians);

    return Vector2{
        cos * x - sin * y,
        sin * x + cos * y
    };
}

} // namespace SGE
