#ifndef _SGE_MESH_H
#define _SGE_MESH_H

#include "material.h"
#include "shader.h"
#include "vertex.h"
#include "vertexbuffer.h"

#include <cstddef>
#include <memory>
#include <vector>

namespace SGE {

class Mesh {
    private:
        GLuint ibo_;
        GLuint vao_;

        // TODO: Make this a smart pointer
        VertexBuffer* vertex_buffer_;

        std::vector<int> indices_;
        Material material_;

        void init();

    public:
        Mesh() = delete;
        explicit Mesh(
                const std::vector<Vertex>& vertices,
                const std::vector<int>& indices,
                const Material& material
                );

        void draw(Shader& shader) const;
        const Material& material() const;
};

} // namespace SGE
#endif
