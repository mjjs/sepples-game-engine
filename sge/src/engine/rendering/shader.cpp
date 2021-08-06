#include "engine/rendering/shader.h"

#include "engine/rendering/graphicsapi.h"
#include "platform/opengl/openglshader.h"

namespace SGE
{

std::shared_ptr<Shader> Shader::create(const std::string& vertex_path,
                                       const std::string& fragment_path)
{
    switch (GraphicsAPI::vendor()) {
    case GraphicsAPI::VENDOR::OPENGL:
        return std::make_shared<OpenGLShader>(vertex_path, fragment_path);
    case GraphicsAPI::VENDOR::VULKAN:
        throw std::runtime_error{"Vulkan is not supported yet!"};
    }
}

std::shared_ptr<Shader> Shader::create(const std::string& shader_name)
{
    switch (GraphicsAPI::vendor()) {
    case GraphicsAPI::VENDOR::OPENGL:
        return std::make_shared<OpenGLShader>(shader_name);
    case GraphicsAPI::VENDOR::VULKAN:
        throw std::runtime_error{"Vulkan is not supported yet!"};
    }
}

} // namespace SGE
