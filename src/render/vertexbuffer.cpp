#include "openglvertexbuffer.h"
#include "vertex.h"
#include "vertexbuffer.h"

#include <vector>

namespace SGE {

VertexBuffer* VertexBuffer::create(const std::vector<Vertex>& vertices)
{
    return new OpenGLVertexBuffer(vertices);
}

} // namespace SGE
