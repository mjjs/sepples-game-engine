#ifndef _GE_SHADER_H
#define _GE_SHADER_H

#include <GL/glew.h>
#include <string>
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
         void bind();
};
#endif
