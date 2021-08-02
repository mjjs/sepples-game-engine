#include "bufferlayout.h"
#include "openglvertexbuffer.h"
#include "vertex.h"
#include "vertexbuffer.h"
#include "graphicsapi.h"

#include <memory>
#include <vector>
#include <stdexcept>

namespace SGE {

std::shared_ptr<VertexBuffer> VertexBuffer::create(
        const std::vector<Vertex>& vertices,
        const BufferLayout layout
        )
{
    switch(GraphicsAPI::vendor()) {
    case GraphicsAPI::VENDOR::OPENGL:
        return std::make_shared<OpenGLVertexBuffer>(vertices, layout);
    case GraphicsAPI::VENDOR::VULKAN:
        throw std::runtime_error{"Vulkan is not supported yet!"};
    }
}

} // namespace SGE
