#include "uniformbuffer.h"
#include "opengluniformbuffer.h"
#include "graphicsapi.h"

#include <cstdint>
#include <memory>
#include <stdexcept>

namespace SGE {

std::shared_ptr<UniformBuffer> UniformBuffer::create(const std::uint32_t size,
        const std::uint32_t binding)
{
    switch(GraphicsAPI::vendor()) {
    case GraphicsAPI::VENDOR::OPENGL:
        return std::make_shared<OpenGLUniformBuffer>(size, binding);
    case GraphicsAPI::VENDOR::VULKAN:
        throw std::runtime_error{"Vulkan is not supported yet!"};
    }
}

} // namespace SGE
