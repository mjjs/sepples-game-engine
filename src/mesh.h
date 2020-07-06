#ifndef _GE_MESH_H
#define _GE_MESH_H

#include "vector3.h"
#include <GL/glew.h>

#include <vector>

class Mesh {
    private:
        GLuint vbo_id;

    public:
        explicit Mesh(const std::vector<Math::Vector3>& vertices);
        void draw() const;

};
#endif
