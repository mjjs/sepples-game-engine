#ifndef _SGE_MESH_H
#define _SGE_MESH_H

#include "material.h"
#include "vertex.h"
#include "vertexarray.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace SGE {

class Shader;

class Mesh {
    private:
        std::shared_ptr<VertexArray> vertex_array_;
        Material material_;

    public:
        Mesh() = delete;
        explicit Mesh(
                const std::vector<Vertex>& vertices,
                const std::vector<std::uint32_t>& indices,
                const Material& material
                );

        void draw(Shader& shader) const;
        const Material& material() const;
};

} // namespace SGE
#endif
