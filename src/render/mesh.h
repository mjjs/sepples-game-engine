#ifndef _GE_MESH_H
#define _GE_MESH_H

#include "vector3.h"
#include <GL/glew.h>

#include <cstddef>
#include <vector>

class Mesh {
    private:
        GLuint vbo_;
        GLuint ibo_;
        std::size_t size_ = 0;

    public:
        Mesh();
        Mesh(const std::vector<Math::Vector3>& vertices, const std::vector<int>& indices);
        void draw() const;
        void set_vertices(const std::vector<Math::Vector3>& vertices, const std::vector<int>& indices);
};
#endif
