#include "resourceloader.h"
#include "shader.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) :
    shader_program_{glCreateProgram()}
{
    if (shader_program_ == 0) {
        throw std::runtime_error{"Shader creation failed"};
    }

    std::string vertex_shader_name = load_shader(vertex_path);
    std::string fragment_shader_name = load_shader(fragment_path);

    add_vertex_shader(vertex_shader_name);
    add_fragment_shader(fragment_shader_name);

    compile_shader();

    add_uniform("transform_u");
    add_uniform("projection_u");
    add_uniform("material_u.ambient");
    add_uniform("material_u.diffuse");
    add_uniform("material_u.specular");
    add_uniform("material_u.shininess");
}

Shader::~Shader()
{
    glDeleteProgram(shader_program_);
}

void Shader::add_vertex_shader(const std::string& shader_name)
{
    add_program(shader_name, GL_VERTEX_SHADER);
}

void Shader::add_geometry_shader(const std::string& shader_name)
{
    add_program(shader_name, GL_GEOMETRY_SHADER);
}

void Shader::add_fragment_shader(const std::string& shader_name)
{
    add_program(shader_name, GL_FRAGMENT_SHADER);
}

void Shader::add_program(const std::string& shader_name, GLenum shader_type)
{
    const GLuint shader = glCreateShader(shader_type);
    if (shader == 0) {
        throw std::runtime_error{"Could not create shader"};
    }

    if (shader == GL_INVALID_ENUM) {
        throw std::runtime_error{"Invalid shader type: " + std::to_string(shader_type)};
    }

    const GLchar* programs[1]{shader_name.c_str()};

    glShaderSource(shader, 1, programs, nullptr);
    glCompileShader(shader);

    std::pair<bool, std::string> error = check_shader_error(ShaderErrorCheckType::SHADER,
            GL_COMPILE_STATUS, shader);

    if (error.first == true) {
        throw std::runtime_error("Could not compile shader: " + error.second);
    }

    glAttachShader(shader_program_, shader);
    attached_shaders_.push_back(shader);
}

void Shader::compile_shader()
{
    glLinkProgram(shader_program_);

    std::pair<bool, std::string> error = check_shader_error(ShaderErrorCheckType::PROGRAM,
            GL_LINK_STATUS, shader_program_);

    if (error.first == true) {
        throw std::runtime_error("Could not link shader: " + error.second);
    }

    glValidateProgram(shader_program_);

    error = check_shader_error(ShaderErrorCheckType::PROGRAM,
            GL_VALIDATE_STATUS, shader_program_);

    if (error.first == true) {
        throw std::runtime_error("Shader not valid: " + error.second);
    }

    for (const GLuint shader : attached_shaders_) {
        glDetachShader(shader_program_, shader);
    }
}

void Shader::bind() const
{
    glUseProgram(shader_program_);
}

std::pair<bool, std::string> Shader::check_shader_error(ShaderErrorCheckType check_type, GLenum check_name,
        GLuint to_check)
{
    GLint success;

    if (check_type == ShaderErrorCheckType::PROGRAM) {
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

    if (check_type == ShaderErrorCheckType::PROGRAM) {
        glGetProgramInfoLog(to_check, sizeof(error_message), &error_length, error_message);
    } else {
        glGetShaderInfoLog(to_check, error_message_max_length, &error_length, error_message);
    }

    return std::pair<bool, std::string>{true, std::string(error_message)};
}

void Shader::add_uniform(const std::string& variable_name) const
{
    if (uniform_variables_.find(variable_name) != uniform_variables_.end()) {
        return;
    }

    const GLint uniform_location = glGetUniformLocation(shader_program_, variable_name.c_str());
    if (uniform_location == -1) {
        std::cerr << "Uniform variable " << variable_name << " not found in the shader program\n";
        return;
    }

    uniform_variables_[variable_name] = uniform_location;
}

void Shader::set_uniform(const std::string& variable_name, int value)
{
    glUniform1i(uniform_variables_[variable_name], value);
}

void Shader::set_uniform(const std::string& variable_name, float value)
{
    glUniform1f(uniform_variables_[variable_name], value);
}

void Shader::set_uniform(const std::string& variable_name, const Math::Vector3& vector)
{
    glUniform3f(uniform_variables_[variable_name], vector.x, vector.y, vector.z);
}

void Shader::set_uniform(const std::string& variable_name, const Math::Matrix4& matrix)
{
    glUniformMatrix4fv(uniform_variables_[variable_name], 1, GL_TRUE, &(matrix[0][0]));
}

void Shader::set_transformations(const Math::Matrix4& transformation,
        const Math::Matrix4& projection)
{
    set_uniform("transform_u", transformation);
    set_uniform("projection_u", projection);
}

void Shader::set_material(const Material& material)
{
    set_uniform("material_u.ambient", material.ambient_colour());
    set_uniform("material_u.diffuse", material.diffuse_colour());
    set_uniform("material_u.specular", material.specular_colour());
    set_uniform("material_u.shininess", material.shininess());
}
