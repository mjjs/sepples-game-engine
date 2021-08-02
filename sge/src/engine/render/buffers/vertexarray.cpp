#include "vertexarray.h"
#include "openglvertexarray.h"

#include <memory>

namespace SGE {

std::shared_ptr<VertexArray> VertexArray::create()
{
    // TODO: Decide this from current platform
    return std::make_shared<OpenGLVertexArray>();
}

} // namespace SGE
