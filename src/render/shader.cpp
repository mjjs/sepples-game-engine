#include "shader.h"
#include <stdexcept>
#include <string>
#include <utility>

Shader::Shader() :
    shader_program{glCreateProgram()}
{
    if (shader_program == 0) {
        throw std::runtime_error{"Shader creation failed"};
    }
}

Shader::~Shader()
{
    glDeleteProgram(shader_program);
}

void Shader::add_vertex_shader(const std::string& shader_code)
{
    add_program(shader_code, GL_VERTEX_SHADER);
}

void Shader::add_geometry_shader(const std::string& shader_code)
{
    add_program(shader_code, GL_GEOMETRY_SHADER);
}

void Shader::add_fragment_shader(const std::string& shader_code)
{
    add_program(shader_code, GL_FRAGMENT_SHADER);
}

void Shader::add_program(const std::string& shader_code, GLenum shader_type)
{
    const GLuint shader = glCreateShader(shader_type);
    if (shader == 0) {
        throw std::runtime_error{"Could not create shader"};
    }

    if (shader == GL_INVALID_ENUM) {
        throw std::runtime_error{"Invalid shader type: " + std::to_string(shader_type)};
    }

    const GLchar* programs[1]{shader_code.c_str()};

    glShaderSource(shader, 1, programs, nullptr);
    glCompileShader(shader);

    std::pair<bool, std::string> error = check_shader_error(ShaderErrorCheckType::shader,
            GL_COMPILE_STATUS, shader);

    if (error.first == true) {
        throw std::runtime_error("Could not compile shader: " + error.second);
    }

    glAttachShader(shader_program, shader);
    attached_shaders.push_back(shader);
}

void Shader::compile_shader()
{
    glLinkProgram(shader_program);

    std::pair<bool, std::string> error = check_shader_error(ShaderErrorCheckType::program,
            GL_LINK_STATUS, shader_program);

    if (error.first == true) {
        throw std::runtime_error("Could not link shader: " + error.second);
    }

    glValidateProgram(shader_program);

    error = check_shader_error(ShaderErrorCheckType::program,
            GL_VALIDATE_STATUS, shader_program);

    if (error.first == true) {
        throw std::runtime_error("Shader not valid: " + error.second);
    }

    for (const GLuint shader : attached_shaders) {
        glDetachShader(shader_program, shader);
    }
}

void Shader::bind()
{
    glUseProgram(shader_program);
}

std::pair<bool, std::string> Shader::check_shader_error(ShaderErrorCheckType check_type, GLenum check_name,
        GLuint to_check)
{
    GLint success;

    if (check_type == ShaderErrorCheckType::program) {
        glGetProgramiv(to_check, check_name, &success);
    } else {
        glGetShaderiv(to_check, check_name, &success);
    }

    if (success != 0) {
        return std::pair<bool, std::string>{false, ""};
    }

    const int error_message_max_length = 1024;
    GLchar error_message[error_message_max_length];
    GLsizei error_length = 0;

    if (check_type == ShaderErrorCheckType::program) {
        glGetProgramInfoLog(to_check, sizeof(error_message), &error_length, error_message);
    } else {
        glGetShaderInfoLog(to_check, error_message_max_length, &error_length, error_message);
    }

    return std::pair<bool, std::string>{true, std::string(error_message)};
}

void Shader::add_uniform(const std::string& variable_name)
{
    const GLint uniform_location = glGetUniformLocation(shader_program, variable_name.c_str());
    if (uniform_location == -1) {
        throw std::runtime_error("Uniform variable " + variable_name + " not found in the shader program");
    }

    uniform_variables[variable_name] = uniform_location;
}

void Shader::set_uniform(const std::string& variable_name, int value)
{
    glUniform1i(uniform_variables[variable_name], value);
}

void Shader::set_uniform(const std::string& variable_name, float value)
{
    glUniform1f(uniform_variables[variable_name], value);
}

void Shader::set_uniform(const std::string& variable_name, const Math::Vector3& vector)
{
    glUniform3f(uniform_variables[variable_name], vector.x, vector.y, vector.z);
}

void Shader::set_uniform(const std::string& variable_name, const Math::Matrix4& matrix)
{
    glUniformMatrix4fv(uniform_variables[variable_name], 1, GL_TRUE, &(matrix[0][0]));
}

