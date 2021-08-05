#include "texture2d.h"

#include "graphicsapi.h"
#include "opengltexture2d.h"
#include "vector3.h"

#include <memory>
#include <stdexcept>
#include <string>

namespace SGE
{

std::shared_ptr<Texture2D> Texture2D::create(const std::string& path,
                                             const Type type)
{
    switch (GraphicsAPI::vendor()) {
    case GraphicsAPI::VENDOR::OPENGL:
        return std::make_shared<OpenGLTexture2D>(path, type);
    case GraphicsAPI::VENDOR::VULKAN:
        throw std::runtime_error{"Vulkan is not supported yet!"};
    }
}

std::shared_ptr<Texture2D> Texture2D::create(const Vector3& colour,
                                             const std::uint32_t width,
                                             const std::uint32_t height)
{
    switch (GraphicsAPI::vendor()) {
    case GraphicsAPI::VENDOR::OPENGL:
        return std::make_shared<OpenGLTexture2D>(colour, width, height);
    case GraphicsAPI::VENDOR::VULKAN:
        throw std::runtime_error{"Vulkan is not supported yet!"};
    }
}

} // namespace SGE