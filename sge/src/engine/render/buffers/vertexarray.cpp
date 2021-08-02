#include "vertexarray.h"
#include "openglvertexarray.h"
#include "graphicsapi.h"

#include <memory>
#include <stdexcept>

namespace SGE {

std::shared_ptr<VertexArray> VertexArray::create()
{
    switch(GraphicsAPI::vendor()) {
    case GraphicsAPI::VENDOR::OPENGL:
        return std::make_shared<OpenGLVertexArray>();
    case GraphicsAPI::VENDOR::VULKAN:
        throw std::runtime_error{"Vulkan is not supported yet!"};
    }
}

} // namespace SGE
