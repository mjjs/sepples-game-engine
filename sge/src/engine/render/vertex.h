#ifndef _SGE_VERTEX_H
#define _SGE_VERTEX_H
#include "vector2.h"
#include "vector3.h"

namespace SGE
{

struct Vertex {
    Vector3 position{};
    Vector3 normal{};
    Vector2 texture_coordinate{};
};

} // namespace SGE
#endif
