#ifndef _GE_MESH_H
#define _GE_MESH_H

#include "material.h"
#include "shader.h"
#include "vertex.h"

#include <GL/glew.h>

#include <cstddef>
#include <vector>

class Mesh {
    private:
        GLuint vbo_;
        GLuint ibo_;
        GLuint vao_;

        std::vector<Vertex> vertices_;
        std::vector<int> indices_;
        Material material_;

        void init();

    public:
        Mesh() = default;
        explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices,
                const Material& material);

        void draw(Shader& shader) const;
};
#endif
