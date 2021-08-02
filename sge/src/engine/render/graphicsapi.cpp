#include "graphicsapi.h"
#include "vector3.h"
#include "openglgraphicsapi.h"

#include <stdexcept>
#include <memory>

namespace SGE {

API GraphicsAPI::api_ = API::OPENGL; // NOLINT

std::unique_ptr<GraphicsAPI> GraphicsAPI::create()
{
    switch(api_) {
        case API::OPENGL:
            return std::make_unique<OpenGLGraphicsAPI>();
        case API::VULKAN:
            throw std::runtime_error("Vulkan is not supported currently");
    }
}

} // namespace SGE
