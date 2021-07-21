#ifndef _SGE_VERTEX_H
#define _SGE_VERTEX_H
#include "vector2.h"
#include "vector3.h"

namespace SGE {

struct Vertex {
    Math::Vector3 position{};
    Math::Vector3 normal{};
    Math::Vector2 texture_coordinate{};
};

} // namespace SGE
#endif
