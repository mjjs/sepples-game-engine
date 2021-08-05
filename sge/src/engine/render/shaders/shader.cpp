#include "shader.h"

#include "resourceloader.h"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace SGE
{

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path)
    : shader_program_{glCreateProgram()}
{
    if (shader_program_ == 0) {
        throw std::runtime_error{"Shader creation failed"};
    }

    std::string vertex_shader_name   = load_shader(vertex_path);
    std::string fragment_shader_name = load_shader(fragment_path);

    add_vertex_shader(vertex_shader_name);
    add_fragment_shader(fragment_shader_name);

    compile_shader();

    add_all_uniforms(vertex_shader_name);
    add_all_uniforms(fragment_shader_name);
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
        throw std::runtime_error{"Invalid shader type: " +
                                 std::to_string(shader_type)};
    }

    const GLchar* programs[1]{shader_name.c_str()};

    glShaderSource(shader, 1, programs, nullptr);
    glCompileShader(shader);

    std::pair<bool, std::string> error = check_shader_error(
        ShaderErrorCheckType::SHADER, GL_COMPILE_STATUS, shader);

    if (error.first == true) {
        throw std::runtime_error("Could not compile shader: " + error.second);
    }

    glAttachShader(shader_program_, shader);
    attached_shaders_.push_back(shader);
}

void Shader::compile_shader()
{
    glLinkProgram(shader_program_);

    std::pair<bool, std::string> error = check_shader_error(
        ShaderErrorCheckType::PROGRAM, GL_LINK_STATUS, shader_program_);

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

std::pair<bool, std::string> Shader::check_shader_error(
    ShaderErrorCheckType check_type, GLenum check_name, GLuint to_check)
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
        glGetProgramInfoLog(to_check, sizeof(error_message), &error_length,
                            error_message);
    } else {
        glGetShaderInfoLog(to_check, error_message_max_length, &error_length,
                           error_message);
    }

    return std::pair<bool, std::string>{true, std::string(error_message)};
}

void Shader::add_uniform(const std::string& variable_name) const
{
    if (uniform_exists(variable_name)) {
        return;
    }

    const GLint uniform_location =
        glGetUniformLocation(shader_program_, variable_name.c_str());
    if (uniform_location == -1) {
        // std::cerr << "Uniform variable " << variable_name << " not found in
        // the shader program\n";
        return;
    }

    uniform_variables_[variable_name] = uniform_location;
}

void Shader::set_uniform(const std::string& variable_name, int value) const
{
    if (!uniform_exists(variable_name)) {
        return;
    }

    glUniform1i(uniform_variables_[variable_name], value);
}

void Shader::set_uniform(const std::string& variable_name, float value) const
{
    if (!uniform_exists(variable_name)) {
        return;
    }

    glUniform1f(uniform_variables_[variable_name], value);
}

void Shader::set_uniform(const std::string& variable_name,
                         const Vector3& vector) const
{
    if (!uniform_exists(variable_name)) {
        return;
    }

    glUniform3f(uniform_variables_[variable_name], vector.x, vector.y,
                vector.z);
}

void Shader::set_uniform(const std::string& variable_name,
                         const Matrix4& matrix) const
{
    if (!uniform_exists(variable_name)) {
        return;
    }

    glUniformMatrix4fv(uniform_variables_[variable_name], 1, GL_TRUE,
                       &(matrix[0][0]));
}

void Shader::set_transformations(const Matrix4& transformation,
                                 const Matrix4& projection) const
{
    set_uniform("transform_u", transformation);
    set_uniform("projection_u", projection);
}

bool Shader::uniform_exists(const std::string& variable_name) const
{
    return uniform_variables_.find(variable_name) != uniform_variables_.end();
}

void Shader::update_uniforms(
    [[maybe_unused]] const Transform& transform,
    [[maybe_unused]] const Material& material,
    [[maybe_unused]] const RenderingEngine& rendering_engine) const
{
}

void Shader::add_all_uniforms(const std::string& shader_code)
{
    auto structs = get_struct_uniforms(shader_code);

    const std::string uniform_keyword = "uniform ";
    std::size_t uniform_pos           = shader_code.find(uniform_keyword);

    while (uniform_pos != std::string::npos) {
        std::size_t semi_pos = shader_code.find(';', uniform_pos);

        bool type_set = false;
        std::string field_name;
        std::string field_type;

        for (auto i = uniform_pos + uniform_keyword.size(); i < semi_pos; ++i) {
            char c = shader_code[i];

            if (std::isspace(c) != 0) {
                if (!type_set && !field_type.empty()) {
                    type_set = true;
                }
                continue;
            }

            if (!type_set) {
                field_type += c;
            } else {
                field_name += c;
            }
        }

        if (structs.find(field_type) == structs.end()) {
            add_uniform(field_name);
        } else {
            add_struct_uniform(field_name, field_type, structs);
        }

        uniform_pos = shader_code.find(uniform_keyword, semi_pos);
    }
}

void Shader::add_struct_uniform(
    const std::string& name, const std::string& type,
    std::unordered_map<std::string, std::vector<UniformField>> structs)
{
    if (!structs.contains(type)) {
        add_uniform(name);
        return;
    }

    auto fields = structs[type];

    for (const auto& field : fields) {
        add_struct_uniform(name + "." + field.name, field.type, structs);
    }
}

std::unordered_map<std::string, std::vector<Shader::UniformField>> Shader::
    get_struct_uniforms(const std::string& shader_code)
{
    auto structs =
        std::unordered_map<std::string, std::vector<Shader::UniformField>>{};

    const std::string struct_keyword = "struct ";

    std::size_t struct_pos = shader_code.find(struct_keyword);

    while (struct_pos != std::string::npos) {
        std::size_t curly_begin = shader_code.find('{', struct_pos);
        std::size_t curly_end   = shader_code.find('}', struct_pos);

        std::string type;
        for (auto i = struct_pos + struct_keyword.size(); i < curly_begin;
             ++i) {
            char c = shader_code[i];

            if (std::isspace(c) == 0) {
                type += c;
            }
        }

        bool type_set = false;
        std::string field_name;
        std::string field_type;
        auto fields = std::vector<Shader::UniformField>{};

        for (auto i = curly_begin + 1; i < curly_end; ++i) {
            char c = shader_code[i];

            if (std::isspace(c) != 0) {
                if (!type_set && !field_type.empty()) {
                    type_set = true;
                }
                continue;
            }

            if (c == ';') {
                type_set = false;
                fields.push_back({field_name, field_type});

                field_name.clear();
                field_type.clear();

                continue;
            }

            if (!type_set) {
                field_type += c;
            } else {
                field_name += c;
            }
        }

        structs[type] = fields;
        struct_pos    = shader_code.find(struct_keyword, curly_end);
    }

    return structs;
}

} // namespace SGE
