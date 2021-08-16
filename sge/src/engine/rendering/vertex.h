#ifndef _SGE_VERTEX_H
#define _SGE_VERTEX_H

#include <glm/glm.hpp>

namespace SGE
{

struct Vertex {
    glm::vec3 position{};
    glm::vec3 normal{};
    glm::vec2 texture_coordinate{};
};

} // namespace SGE
#endif
