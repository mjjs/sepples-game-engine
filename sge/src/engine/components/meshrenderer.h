#ifndef _SGE_MESHRENDERER_H
#define _SGE_MESHRENDERER_H

#include "engine/rendering/shaders/basicshader.h"
#include "engine/components/camera.h"
#include "engine/components/gamecomponent.h"
#include "engine/rendering/material.h"
#include "engine/rendering/mesh.h"
#include "engine/rendering/renderingengine.h"
#include "engine/rendering/shaders/shader.h"
#include "engine/core/transform.h"

#include <memory>

namespace SGE
{

class MeshRenderer : public GameComponent
{
  private:
    std::shared_ptr<Mesh> mesh_;

  public:
    MeshRenderer(std::shared_ptr<Mesh>& mesh);

    void render(const Transform& transform, Shader& shader,
                const RenderingEngine& rendering_engine) override;
};

} // namespace SGE
#endif
