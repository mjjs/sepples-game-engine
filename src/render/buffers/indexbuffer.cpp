#include "indexbuffer.h"
#include "openglindexbuffer.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace SGE {

std::shared_ptr<IndexBuffer> IndexBuffer::create(const std::vector<std::uint32_t>& indices)
{
    // TODO: Decide this from current platform
    return std::make_shared<OpenGLIndexBuffer>(indices);
}

} // namespace SGE
