#ifndef _SGE_MESH_H
#define _SGE_MESH_H

#include "indexbuffer.h"
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
        GLuint vao_;

        // TODO: Make this a smart pointer
        VertexBuffer* vertex_buffer_;
        IndexBuffer* index_buffer_;

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
