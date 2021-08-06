#include "engine/ecs/components/meshrenderercomponent.h"

#include "engine/rendering/mesh.h"

#include <memory>

namespace SGE
{

MeshRendererComponent::MeshRendererComponent(const std::shared_ptr<Mesh>& mesh)
    : mesh_{mesh}
{
}

const std::shared_ptr<Mesh>& MeshRendererComponent::mesh() const
{
    return mesh_;
}

std::shared_ptr<Mesh> MeshRendererComponent::mesh()
{
    return mesh_;
}

} // namespace SGE
