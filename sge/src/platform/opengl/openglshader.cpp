#include "platform/opengl/openglshader.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <glad/glad.h>
#include <sstream>
#include <string>
#include <utility>

namespace SGE
{

enum class ShaderErrorCheckType { PROGRAM, SHADER };
static std::string read_shader_code(const std::string& path);
static std::pair<bool, std::string> check_shader_error(
    ShaderErrorCheckType check_type, GLenum check_name, GLuint shader_id);

OpenGLShader::OpenGLShader(const std::string& vertex_path,
                           const std::string& fragment_path)
{
    shader_id_ = glCreateProgram();

    const std::string vertex_src = read_shader_code(vertex_path);
    GLuint vertex_program_id = compile_program(vertex_src, GL_VERTEX_SHADER);

    const std::string fragment_src = read_shader_code(fragment_path);
    GLuint fragment_program_id =
        compile_program(fragment_src, GL_FRAGMENT_SHADER);

    link();

    glDetachShader(shader_id_, vertex_program_id);
    glDetachShader(shader_id_, fragment_program_id);
    glDeleteShader(vertex_program_id);
    glDeleteShader(fragment_program_id);
}

OpenGLShader::OpenGLShader(const std::string& shader_name)
    : OpenGLShader{shader_name + "_vertex.glsl", shader_name + "_fragment.glsl"}
{
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(shader_id_);
}

GLuint OpenGLShader::compile_program(const std::string& shader_src,
                                     GLenum shader_type) const
{
    const GLuint shader = glCreateShader(shader_type);

    assert(shader);                    // NOLINT
    assert(shader != GL_INVALID_ENUM); // NOLINT

    auto programs = std::array<const GLchar*, 1>{shader_src.c_str()};

    glShaderSource(shader, 1, programs.data(), nullptr);
    glCompileShader(shader);

    auto [compile_failed, error_message] = check_shader_error(
        ShaderErrorCheckType::SHADER, GL_COMPILE_STATUS, shader);

    if (compile_failed) {
        throw std::runtime_error{"Could not compile shader: " + error_message};
    }

    glAttachShader(shader_id_, shader);

    return shader;
}

void OpenGLShader::link() const
{
    glLinkProgram(shader_id_);

    auto [linking_failed, linking_error] = check_shader_error(
        ShaderErrorCheckType::PROGRAM, GL_LINK_STATUS, shader_id_);

    if (linking_failed) {
        throw std::runtime_error("Could not link shader: " + linking_error);
    }

    glValidateProgram(shader_id_);

    auto [validation_failed, validate_error] = check_shader_error(
        ShaderErrorCheckType::PROGRAM, GL_VALIDATE_STATUS, shader_id_);

    if (validation_failed) {
        throw std::runtime_error("Shader not valid: " + validate_error);
    }
}

void OpenGLShader::bind() const
{
    glUseProgram(shader_id_);
}

void OpenGLShader::unbind() const
{
    glUseProgram(0);
}

GLuint OpenGLShader::register_uniform_if_not_exists(
    const std::string& variable_name)
{
    if (!uniform_locations_.contains(variable_name)) {
        uniform_locations_[variable_name] =
            glGetUniformLocation(shader_id_, variable_name.c_str());
    }

    return uniform_locations_[variable_name];
}

void OpenGLShader::set_uniform(const std::string& variable_name, int value)
{
    GLuint location = register_uniform_if_not_exists(variable_name);
    glUniform1i(location, value);
}

void OpenGLShader::set_uniform(const std::string& variable_name, float value)
{
    GLuint location = register_uniform_if_not_exists(variable_name);
    glUniform1f(location, value);
}

void OpenGLShader::set_uniform(const std::string& variable_name,
                               const Vector3& vector)
{
    GLuint location = register_uniform_if_not_exists(variable_name);
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void OpenGLShader::set_uniform(const std::string& variable_name,
                               const Matrix4& matrix)
{
    GLuint location = register_uniform_if_not_exists(variable_name);
    glUniformMatrix4fv(location, 1, GL_TRUE, &(matrix[0][0]));
}

static std::string read_shader_code(const std::string& path)
{
    std::ifstream shader_file{path, std::ios_base::in};
    std::stringstream ss{};
    ss << shader_file.rdbuf();
    shader_file.close();

    return ss.str();
}

static std::pair<bool, std::string> check_shader_error(
    ShaderErrorCheckType check_type, GLenum check_name, GLuint shader_id)
{
    GLint success{0};

    switch (check_type) {
    case ShaderErrorCheckType::SHADER:
        glGetShaderiv(shader_id, check_name, &success);
    case ShaderErrorCheckType::PROGRAM:
        glGetProgramiv(shader_id, check_name, &success);
    }

    if (success != 0) {
        return {false, ""};
    }

    const int error_message_max_length = 1024;
    auto error_message = std::array<GLchar, error_message_max_length>{};

    switch (check_type) {
    case ShaderErrorCheckType::SHADER:
        glGetShaderInfoLog(shader_id, error_message_max_length, nullptr,
                           error_message.data());
    case ShaderErrorCheckType::PROGRAM:
        glGetProgramInfoLog(shader_id, error_message_max_length, nullptr,
                            error_message.data());
    }

    return {true, std::string(error_message.begin(), error_message.end())};
}

} // namespace SGE
