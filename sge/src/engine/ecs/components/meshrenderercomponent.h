#ifndef _SGE_MESH_RENDERER_COMPONENT_H
#define _SGE_MESH_RENDERER_COMPONENT_H

#include "engine/rendering/mesh.h"

#include <memory>

namespace SGE
{

class MeshRendererComponent
{
  private:
    std::shared_ptr<Mesh> mesh_;

  public:
    MeshRendererComponent() = default;
    MeshRendererComponent(const std::shared_ptr<Mesh>& mesh);

    const std::shared_ptr<Mesh>& mesh() const;
    std::shared_ptr<Mesh> mesh();
};

} // namespace SGE

#endif
