#include "openglindexbuffer.h"
#include "vertex.h"
#include "indexbuffer.h"

#include <vector>

namespace SGE {

IndexBuffer* IndexBuffer::create(const std::vector<int>& indices)
{
    // TODO: Decide this from current platform
    return new OpenGLIndexBuffer(indices);
}

} // namespace SGE
