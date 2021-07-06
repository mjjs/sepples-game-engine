#ifndef _SGE_SHADER_H
#define _SGE_SHADER_H

#include "vector3.h"
#include "material.h"
#include "matrix4.h"
#include "transform.h"

#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <memory>

namespace SGE {
    class RenderingEngine;
}

enum ShaderErrorCheckType {
    PROGRAM,
    SHADER,
};

class Shader {
    private:
        GLuint shader_program_;
        std::vector<GLuint> attached_shaders_{};
        mutable std::unordered_map<std::string, GLint> uniform_variables_{};

        void add_program(const std::string& shader_name, GLenum shader_type);
        static std::pair<bool, std::string> check_shader_error(ShaderErrorCheckType check_type,
                GLenum check_name, GLuint to_check);

        void add_vertex_shader(const std::string& shader_name);
        void add_geometry_shader(const std::string& shader_name);
        void add_fragment_shader(const std::string& shader_name);

        void compile_shader();

        bool uniform_exists(const std::string& variable_name) const;

    public:
        Shader(const std::string& vertex_path, const std::string& fragment_path);
        ~Shader();

        Shader(const Shader&) = delete;
        Shader(const Shader&&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader& operator=(const Shader&&) = delete;

        void add_uniform(const std::string& variable_name) const;
        void set_uniform(const std::string& variable_name, int value);
        void set_uniform(const std::string& variable_name, float value);
        void set_uniform(const std::string& variable_name, const Math::Vector3& vector);
        void set_uniform(const std::string& variable_name, const Math::Matrix4& matrix);

        void bind() const;
        virtual void update_uniforms(
                const Math::Transform& transform,
                const Material& material,
                const SGE::RenderingEngine& rendering_engine) = 0;

        void set_material(const Material& material);
        void set_transformations(const Math::Matrix4& transformation,
                const Math::Matrix4& projection);
};
#endif
