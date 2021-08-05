#include "engine/rendering/graphicsapi.h"
#include "engine/math/vector3.h"
#include "platform/opengl/openglgraphicsapi.h"

#include <stdexcept>
#include <memory>

namespace SGE {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
GraphicsAPI::VENDOR GraphicsAPI::vendor_ = VENDOR::OPENGL;

std::unique_ptr<GraphicsAPI> GraphicsAPI::create()
{
    switch(GraphicsAPI::vendor()) {
    case GraphicsAPI::VENDOR::OPENGL:
            return std::make_unique<OpenGLGraphicsAPI>();
    case GraphicsAPI::VENDOR::VULKAN:
        throw std::runtime_error{"Vulkan is not supported yet!"};
    }
}

GraphicsAPI::VENDOR GraphicsAPI::vendor()
{
    return vendor_;
}

} // namespace SGE
