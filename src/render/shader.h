#ifndef _GE_SHADER_H
#define _GE_SHADER_H

#include "vector3.h"
#include "matrix4.h"

#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

enum ShaderErrorCheckType {
    program,
    shader,
};

class Shader {
    private:
         GLuint shader_program;
         std::vector<GLuint> attached_shaders{};
         std::unordered_map<std::string, GLint> uniform_variables{};

         void add_program(const std::string& shader_name, GLenum shader_type);
         static std::pair<bool, std::string> check_shader_error(ShaderErrorCheckType check_type,
                 GLenum check_name, GLuint to_check);
    public:
         Shader();
         ~Shader();

         void add_vertex_shader(const std::string& shader_name);
         void add_geometry_shader(const std::string& shader_name);
         void add_fragment_shader(const std::string& shader_name);
         void compile_shader();

         void add_uniform(const std::string& variable_name);
         void set_uniform(const std::string& variable_name, int value);
         void set_uniform(const std::string& variable_name, float value);
         void set_uniform(const std::string& variable_name, const Math::Vector3& vector);
         void set_uniform(const std::string& variable_name, const Math::Matrix4& matrix);

         void bind();
};
#endif
