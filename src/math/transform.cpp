#include "transform.h"
#include "matrix4.h"
#include "vector3.h"

Math::Transform::Transform(const Vector3& translation) :
    translation{translation}
{}

Math::Matrix4 Math::Transform::get_transformation() const
{
    return Math::Matrix4::translation(translation);
}
