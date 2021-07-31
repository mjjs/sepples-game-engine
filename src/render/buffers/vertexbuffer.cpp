#include "openglvertexbuffer.h"
#include "vertex.h"
#include "vertexbuffer.h"

#include <vector>

namespace SGE {

VertexBuffer* VertexBuffer::create(const std::vector<Vertex>& vertices)
{
    // TODO: Decide this from current platform
    return new OpenGLVertexBuffer(vertices);
}

} // namespace SGE
