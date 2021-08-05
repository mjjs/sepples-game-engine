#ifndef _SGE_SHADER_H
#define _SGE_SHADER_H

#include "engine/rendering/material.h"
#include "engine/math/matrix4.h"
#include "engine/core/transform.h"
#include "engine/math/vector3.h"

#include <glad/glad.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace SGE
{

class RenderingEngine;

class Shader
{
  private:
    enum ShaderErrorCheckType { PROGRAM, SHADER };
    struct UniformField {
        std::string name;
        std::string type;
    };

    GLuint shader_program_;
    std::vector<GLuint> attached_shaders_{};
    mutable std::unordered_map<std::string, GLint> uniform_variables_{};

    void add_program(const std::string& shader_name, GLenum shader_type);
    static std::pair<bool, std::string> check_shader_error(
        ShaderErrorCheckType check_type, GLenum check_name, GLuint to_check);

    void add_vertex_shader(const std::string& shader_name);
    void add_geometry_shader(const std::string& shader_name);
    void add_fragment_shader(const std::string& shader_name);

    void compile_shader();

    bool uniform_exists(const std::string& variable_name) const;

    void add_all_uniforms(const std::string& shader_code);

    static std::unordered_map<std::string, std::vector<UniformField>>
    get_struct_uniforms(const std::string& shader_code);

    void add_struct_uniform(
        const std::string& name, const std::string& type,
        std::unordered_map<std::string, std::vector<UniformField>> structs);

  public:
    Shader(const std::string& vertex_path, const std::string& fragment_path);
    virtual ~Shader();

    Shader(const Shader&)  = delete;
    Shader(const Shader&&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader& operator=(const Shader&&) = delete;

    void add_uniform(const std::string& variable_name) const;
    void set_uniform(const std::string& variable_name, int value) const;
    void set_uniform(const std::string& variable_name, float value) const;
    void set_uniform(const std::string& variable_name,
                     const Vector3& vector) const;
    void set_uniform(const std::string& variable_name,
                     const Matrix4& matrix) const;

    void bind() const;
    virtual void update_uniforms(const Transform& transform,
                                 const Material& material,
                                 const RenderingEngine& rendering_engine) const;

    void set_transformations(const Matrix4& transformation,
                             const Matrix4& projection) const;
};

} // namespace SGE
#endif