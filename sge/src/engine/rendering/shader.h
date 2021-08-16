#ifndef _SGE_SHADER_H
#define _SGE_SHADER_H


#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

namespace SGE
{

class Renderer;

class Shader
{
  public:
    Shader()          = default;
    virtual ~Shader() = default;

    Shader(const Shader&)  = delete;
    Shader(const Shader&&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader& operator=(const Shader&&) = delete;

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual void set_uniform(const std::string& variable_name, int value)   = 0;
    virtual void set_uniform(const std::string& variable_name, float value) = 0;
    virtual void set_uniform(const std::string& variable_name,
                             const glm::vec3& vector)                       = 0;
    virtual void set_uniform(const std::string& variable_name,
                             const glm::mat4& matrix)                       = 0;

    static std::shared_ptr<Shader> create(const std::string& vertex_path,
                                          const std::string& fragment_path);

    static std::shared_ptr<Shader> create(const std::string& shader_name);
};

} // namespace SGE
#endif
