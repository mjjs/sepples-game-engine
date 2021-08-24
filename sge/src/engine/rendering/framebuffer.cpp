#include "engine/rendering/framebuffer.h"

#include "engine/rendering/graphicsapi.h"
#include "platform/opengl/openglframebuffer.h"

#include <memory>

namespace SGE
{

std::shared_ptr<Framebuffer> Framebuffer::create(
    const FramebufferConfig& config)
{
    switch (GraphicsAPI::vendor()) {
    case GraphicsAPI::VENDOR::OPENGL:
        return std::make_shared<OpenGLFramebuffer>(config);
    case GraphicsAPI::VENDOR::VULKAN:
        throw std::runtime_error{"Vulkan is not supported yet!"};
    }
}

} // namespace SGE
