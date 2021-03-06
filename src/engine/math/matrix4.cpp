#include "sgemath.h"
#include "matrix4.h"
#include "vector3.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <sstream>
#include <stdexcept>

Math::Matrix4::Matrix4() : matrix{std::array<std::array<float, 4>, 4>()}
{
    for (std::size_t i = 0; i < 4; ++i) {
        std::array<float, 4> a{};
        a.fill(0);
        matrix[i] = a;
    }
}

Math::Matrix4::Matrix4(const std::array<std::array<float, 4>, 4>& columns_and_rows)
    : matrix{columns_and_rows}
{}

Math::Matrix4 Math::Matrix4::identity()
{
    Math::Matrix4 m{};

    for (std::size_t i = 0; i < 4; ++i) {
        m[i][i] = 1;
    }

    return m;
}

Math::Matrix4 Math::Matrix4::translation(const Math::Vector3& translation_vector)
{
    Math::Matrix4 translation_matrix = Math::Matrix4::identity();
    translation_matrix[0][3] = translation_vector.x;
    translation_matrix[1][3] = translation_vector.y;
    translation_matrix[2][3] = translation_vector.z;
    return translation_matrix;
}

Math::Matrix4 Math::Matrix4::rotation(const Math::Vector3& rotation_vector)
{
    Math::Matrix4 rotate_x = Math::Matrix4::identity();
    Math::Matrix4 rotate_y = Math::Matrix4::identity();
    Math::Matrix4 rotate_z = Math::Matrix4::identity();

    const float x_rads = Math::to_radians(rotation_vector.x);
    const float y_rads = Math::to_radians(rotation_vector.y);
    const float z_rads = Math::to_radians(rotation_vector.z);

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

Math::Matrix4 Math::Matrix4::scale(const Math::Vector3& scale_vector)
{
    Math::Matrix4 scale_matrix = Math::Matrix4::identity();

    scale_matrix[0][0] = scale_vector.x;
    scale_matrix[1][1] = scale_vector.y;
    scale_matrix[2][2] = scale_vector.z;

    return scale_matrix;
}

Math::Matrix4 Math::Matrix4::projection(
        const float fov,
        const float width,
        const float height,
        const float z_near,
        const float z_far)
{
    const float aspect_ratio = width / height;
    const float tan_half_fov = std::tan(Math::to_radians(fov / 2));
    const float z_range = z_near - z_far;

    Math::Matrix4 projection_matrix = Math::Matrix4::identity();
    projection_matrix[0][0] = 1.0F / (tan_half_fov * aspect_ratio);
    projection_matrix[1][1] = 1.0F / tan_half_fov;
    projection_matrix[2][2] = (-z_near - z_far) / z_range;
    projection_matrix[2][3] = 2.0F * z_far * z_near / z_range;
    projection_matrix[3][2] = 1.0F;
    projection_matrix[3][3] = 0.0F;

    return projection_matrix;
}

Math::Matrix4 Math::Matrix4::camera(const Math::Vector3& forward, const Math::Vector3& up)
{
    Math::Vector3 normalized_forward = Math::normalize(forward);
    Math::Vector3 normalized_right = Math::normalize(up);
    normalized_right = Math::cross(normalized_right, normalized_forward);

    Math::Vector3 normalized_up = Math::cross(normalized_forward, normalized_right);

    Math::Matrix4 camera_matrix = Math::Matrix4::identity();
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

Math::Matrix4 operator*(const Math::Matrix4& lhs, const Math::Matrix4& rhs)
{
    Math::Matrix4 result{};

    for (size_t y = 0; y < 4; ++y) {
        for (size_t x = 0; x < 4; ++x) {
            for (size_t k = 0; k < 4; ++k) {
                result[y][x] += lhs[y][k] * rhs[k][x];
            }
        }
    }

    return result;
}

std::array<float, 4>& Math::Matrix4::operator[](const std::size_t i)
{
    return matrix[i];
}

const std::array<float, 4>& Math::Matrix4::operator[](const std::size_t i) const
{
    return matrix[i];
}

std::ostream& operator<<(std::ostream& os, const Math::Matrix4& matrix)
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
