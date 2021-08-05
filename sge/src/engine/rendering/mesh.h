#ifndef _SGE_MESH_H
#define _SGE_MESH_H

#include "engine/rendering/material.h"
#include "engine/rendering/vertex.h"
#include "engine/rendering/buffers/vertexarray.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace SGE
{

class Shader;

class Mesh
{
  private:
    std::shared_ptr<VertexArray> vertex_array_;
    Material material_;

  public:
    Mesh() = delete;
    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<std::uint32_t>& indices, const Material& material);

    void draw(Shader& shader) const;
    const Material& material() const;
};

} // namespace SGE
#endif