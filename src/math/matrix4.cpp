#include "matrix4.h"
#include "vector3.h"

#include <algorithm>
#include <array>
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
