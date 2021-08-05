#include "engine/math/sgemath.h"
#include "engine/math/matrix4.h"
#include "engine/math/vector3.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <sstream>
#include <stdexcept>

namespace SGE {

Matrix4::Matrix4() : matrix{std::array<std::array<float, 4>, 4>()}
{
    for (std::size_t i = 0; i < 4; ++i) {
        std::array<float, 4> a{};
        a.fill(0);
        matrix[i] = a;
    }
}

Matrix4::Matrix4(const std::array<std::array<float, 4>, 4>& columns_and_rows)
    : matrix{columns_and_rows}
{}

Matrix4 Matrix4::identity()
{
    Matrix4 m{};

    for (std::size_t i = 0; i < 4; ++i) {
        m[i][i] = 1;
    }

    return m;
}

Matrix4 Matrix4::translation(const Vector3& translation_vector)
{
    Matrix4 translation_matrix = Matrix4::identity();
    translation_matrix[0][3] = translation_vector.x;
    translation_matrix[1][3] = translation_vector.y;
    translation_matrix[2][3] = translation_vector.z;
    return translation_matrix;
}

Matrix4 Matrix4::rotation(const Vector3& rotation_vector)
{
    Matrix4 rotate_x = Matrix4::identity();
    Matrix4 rotate_y = Matrix4::identity();
    Matrix4 rotate_z = Matrix4::identity();

    const float x_rads = to_radians(rotation_vector.x);
    const float y_rads = to_radians(rotation_vector.y);
    const float z_rads = to_radians(rotation_vector.z);

    rotate_x[1][1] = std::cos(x_rads);
    rotate_x[1][2] = -std::sin(x_rads);
    rotate_x[2][1] = std::sin(x_rads);
    rotate_x[2][2] = std::cos(x_rads);

    rotate_y[0][0] = std::cos(y_rads);
    rotate_y[0][2] = -std::sin(y_rads);
    rotate_y[2][0] = std::sin(y_rads);
    rotate_y[2][2] = std::cos(y_rads);

    rotate_z[0][0] = std::cos(z_rads);
    rotate_z[0][1] = -std::sin(z_rads);
    rotate_z[1][0] = std::sin(z_rads);
    rotate_z[1][1] = std::cos(z_rads);

    return rotate_x * rotate_y * rotate_z;
}

Matrix4 Matrix4::rotation(const Vector3& forward, const Vector3& up, const Vector3& right)
{
    Matrix4 m{};

    m[0][0] = right.x;
    m[0][1] = right.y;
    m[0][2] = right.z;

    m[1][0] = up.x;
    m[1][1] = up.y;
    m[1][2] = up.z;

    m[2][0] = forward.x;
    m[2][1] = forward.y;
    m[2][2] = forward.z;

    m[3][3] = 1;

    return m;
}

Matrix4 Matrix4::scale(const Vector3& scale_vector)
{
    Matrix4 scale_matrix = Matrix4::identity();

    scale_matrix[0][0] = scale_vector.x;
    scale_matrix[1][1] = scale_vector.y;
    scale_matrix[2][2] = scale_vector.z;

    return scale_matrix;
}

Matrix4 Matrix4::perspective(
        const float fov_degrees,
        const float aspect_ratio,
        const float z_near,
        const float z_far)
{
    const float fov_radians = SGE::to_radians(fov_degrees);

    const float tan_half_fov = std::tan(fov_radians / 2);
    const float z_range = z_near - z_far;

    Matrix4 projection_matrix = Matrix4::identity();
    projection_matrix[0][0] = 1.0F / (tan_half_fov * aspect_ratio);
    projection_matrix[1][1] = 1.0F / tan_half_fov;
    projection_matrix[2][2] = (-z_near - z_far) / z_range;
    projection_matrix[2][3] = 2.0F * z_far * z_near / z_range;
    projection_matrix[3][2] = 1.0F;
    projection_matrix[3][3] = 0.0F;

    return projection_matrix;
}

Matrix4 Matrix4::ortographic(
        const float left,
        const float right,
        const float bottom,
        const float top,
        const float near,
        const float far)
{
    const float width = right - left;
    const float height = top - bottom;
    const float depth = far - near;

    Matrix4 ortographic_matrix = Matrix4::identity();
    ortographic_matrix[0][0] = 2/width;
    ortographic_matrix[0][3] = -(right + left)/width;

    ortographic_matrix[1][1] = 2/height;
    ortographic_matrix[1][3] = -(top + bottom)/height;

    ortographic_matrix[2][2] = -2/depth;
    ortographic_matrix[2][3] = -(far + near)/depth;

    return ortographic_matrix;
}

Matrix4 Matrix4::camera(const Vector3& forward, const Vector3& up)
{
    Vector3 normalized_forward = normalize(forward);
    Vector3 normalized_right = normalize(up);
    normalized_right = cross(normalized_right, normalized_forward);

    Vector3 normalized_up = cross(normalized_forward, normalized_right);

    Matrix4 camera_matrix = Matrix4::identity();
    camera_matrix[0][0] = normalized_right.x;
    camera_matrix[0][1] = normalized_right.y;
    camera_matrix[0][2] = normalized_right.z;

    camera_matrix[1][0] = normalized_up.x;
    camera_matrix[1][1] = normalized_up.y;
    camera_matrix[1][2] = normalized_up.z;

    camera_matrix[2][0] = normalized_forward.x;
    camera_matrix[2][1] = normalized_forward.y;
    camera_matrix[2][2] = normalized_forward.z;

    return camera_matrix;
}

Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
{
    Matrix4 result{};

    for (size_t y = 0; y < 4; ++y) {
        for (size_t x = 0; x < 4; ++x) {
            for (size_t k = 0; k < 4; ++k) {
                result[y][x] += lhs[y][k] * rhs[k][x];
            }
        }
    }

    return result;
}

std::array<float, 4>& Matrix4::operator[](const std::size_t i)
{
    return matrix[i];
}

const std::array<float, 4>& Matrix4::operator[](const std::size_t i) const
{
    return matrix[i];
}

std::ostream& operator<<(std::ostream& os, const Matrix4& matrix)
{
    for (size_t i = 0; i < 4; ++i) {
        os << "[";

        for (size_t j = 0; j < 4; ++j) {
            os << matrix[j][i];

            if (j < 3) {
                os << ",\t";
            }
        }

        os << "]";

        if (i < 3) {
            os << '\n';
        }
    }

    return os;
}

} // namespace SGE
