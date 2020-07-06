#include "shader.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <utility>

Shader::Shader() :
    shader_program{glCreateProgram()}
{
    if (shader_program == 0) {
        throw std::runtime_error{"Shader creation failed"};
    }
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
