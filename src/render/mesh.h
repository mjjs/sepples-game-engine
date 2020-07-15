#ifndef _GE_MESH_H
#define _GE_MESH_H

#include "shader.h"
#include "texture.h"
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
        std::vector<Texture> textures_;

        void init();

    public:
        Mesh() = delete;
        explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices,
                const std::vector<Texture>& textures);

        void draw(Shader& shader) const;
};
#endif
