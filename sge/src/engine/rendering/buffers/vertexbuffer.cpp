#include "engine/rendering/buffers/vertexbuffer.h"

#include "engine/rendering/buffers/bufferlayout.h"
#include "engine/rendering/graphicsapi.h"
#include "engine/rendering/vertex.h"
#include "platform/opengl/openglvertexbuffer.h"

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vector>

namespace SGE
{

std::shared_ptr<VertexBuffer> VertexBuffer::create(
    const std::vector<Vertex>& vertices, const BufferLayout layout)
{
    switch (GraphicsAPI::vendor()) {
    case GraphicsAPI::VENDOR::OPENGL:
        return std::make_shared<OpenGLVertexBuffer>(vertices, layout);
    case GraphicsAPI::VENDOR::VULKAN:
        throw std::runtime_error{"Vulkan is not supported yet!"};
    }
}

std::shared_ptr<VertexBuffer> VertexBuffer::create(const std::uint32_t size)
{
    switch (GraphicsAPI::vendor()) {
    case GraphicsAPI::VENDOR::OPENGL:
        return std::make_shared<OpenGLVertexBuffer>(size);
    case GraphicsAPI::VENDOR::VULKAN:
        throw std::runtime_error{"Vulkan is not supported yet!"};
    }
}

} // namespace SGE
