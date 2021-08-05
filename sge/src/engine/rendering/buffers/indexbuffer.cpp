#include "indexbuffer.h"
#include "openglindexbuffer.h"
#include "graphicsapi.h"

#include <cstdint>
#include <memory>
#include <vector>
#include <stdexcept>

namespace SGE {

std::shared_ptr<IndexBuffer> IndexBuffer::create(const std::vector<std::uint32_t>& indices)
{
    switch(GraphicsAPI::vendor()) {
    case GraphicsAPI::VENDOR::OPENGL:
        return std::make_shared<OpenGLIndexBuffer>(indices);
    case GraphicsAPI::VENDOR::VULKAN:
        throw std::runtime_error{"Vulkan is not supported yet!"};
    }
}

} // namespace SGE
