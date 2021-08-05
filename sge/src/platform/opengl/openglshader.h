#ifndef _SGE_OPENGL_SHADER_H
#define _SGE_OPENGL_SHADER_H

#include "engine/rendering/shader.h"

#include <cstdint>
#include <glad/glad.h>
#include <unordered_map>

namespace SGE
{

class OpenGLShader : public Shader
{
  private:
    std::uint32_t shader_id_;
    std::unordered_map<std::string, GLint> uniform_locations_;

    GLuint compile_program(const std::string& shader_src,
                           GLenum shader_type) const;
    void link() const;

    GLuint register_uniform_if_not_exists(const std::string& variable_name);

  public:
    OpenGLShader(const std::string& vertex_path,
                 const std::string& fragment_path);
    ~OpenGLShader();

    OpenGLShader(const OpenGLShader&)  = delete;
    OpenGLShader(const OpenGLShader&&) = delete;
    OpenGLShader& operator=(const OpenGLShader&) = delete;
    OpenGLShader& operator=(const OpenGLShader&&) = delete;

    void bind() const override;
    void unbind() const override;

    void set_uniform(const std::string& variable_name, int value) override;
    void set_uniform(const std::string& variable_name, float value) override;
    void set_uniform(const std::string& variable_name,
                     const Vector3& vector) override;
    void set_uniform(const std::string& variable_name,
                     const Matrix4& matrix) override;
};

} // namespace SGE

#endif
