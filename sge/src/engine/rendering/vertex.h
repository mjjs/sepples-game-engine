#ifndef _SGE_VERTEX_H
#define _SGE_VERTEX_H
#include "engine/math/vector2.h"
#include "engine/math/vector3.h"

namespace SGE
{

struct Vertex {
    Vector3 position{};
    Vector3 normal{};
    Vector2 texture_coordinate{};
};

} // namespace SGE
#endif
