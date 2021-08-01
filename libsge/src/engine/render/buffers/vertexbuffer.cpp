#include "bufferlayout.h"
#include "openglvertexbuffer.h"
#include "vertex.h"
#include "vertexbuffer.h"

#include <memory>
#include <vector>

namespace SGE {

std::shared_ptr<VertexBuffer> VertexBuffer::create(
        const std::vector<Vertex>& vertices,
        const BufferLayout layout
        )
{
    // TODO: Decide this from current platform
    return std::make_shared<OpenGLVertexBuffer>(vertices, layout);
}

} // namespace SGE
