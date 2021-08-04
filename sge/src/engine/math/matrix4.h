#ifndef _SGE_MATRIX_4_H
#define _SGE_MATRIX_4_H

#include "vector3.h"

#include <array>
#include <cstddef>
#include <ostream>

namespace SGE
{

class Matrix4
{
  private:
    std::array<std::array<float, 4>, 4> matrix;

  public:
    Matrix4();
    explicit Matrix4(
        const std::array<std::array<float, 4>, 4>& columns_and_rows);
    static Matrix4 identity();
    static Matrix4 translation(const Vector3& translation_vector);
    static Matrix4 rotation(const Vector3& rotation_vector);
    static Matrix4 rotation(const Vector3& forward, const Vector3& up,
                            const Vector3& right);
    static Matrix4 scale(const Vector3& scale_vector);
    static Matrix4 perspective(float fov_degrees, float aspect_ratio,
                               float z_near, float z_far);
    static Matrix4 ortographic(float left, float right, float bottom, float top,
                               float near, float far);
    static Matrix4 camera(const Vector3& forward, const Vector3& up);

    std::array<float, 4>& operator[](std::size_t i);
    const std::array<float, 4>& operator[](std::size_t i) const;
};

SGE::Matrix4 operator*(const SGE::Matrix4& lhs, const SGE::Matrix4& rhs);
std::ostream& operator<<(std::ostream& os, const SGE::Matrix4& matrix);

} // namespace SGE

#endif
