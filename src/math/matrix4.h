#ifndef _GE_MATRIX_4_H
#define _GE_MATRIX_4_H

#include <array>
#include <cstddef>
#include <ostream>

namespace Math {
class Matrix4 {
    private:
        std::array<std::array<int, 4>, 4> matrix;
    public:
        Matrix4();
        explicit Matrix4(const std::array<std::array<int, 4>, 4>& columns_and_rows);
        static Matrix4 identity();

    std::array<int, 4>& operator[](std::size_t i);
    const std::array<int, 4>& operator[](std::size_t i) const;
};
} // namespace Math

Math::Matrix4 operator*(const Math::Matrix4& lhs, const Math::Matrix4& rhs);
std::ostream& operator<<(std::ostream& os, const Math::Matrix4& matrix);
#endif
