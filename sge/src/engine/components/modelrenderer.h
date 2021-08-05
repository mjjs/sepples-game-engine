#ifndef _TESTGAME_MODELRENDERER_H
#define _TESTGAME_MODELRENDERER_H

#include "engine/rendering/shaders/basicshader.h"
#include "engine/components/camera.h"
#include "engine/components/gamecomponent.h"
#include "engine/core/input.h"
#include "engine/rendering/mesh.h"
#include "engine/rendering/model.h"
#include "engine/rendering/renderingengine.h"
#include "engine/rendering/shaders/shader.h"
#include "engine/core/transform.h"

namespace SGE
{

class ModelRenderer : public GameComponent
{
  private:
    Model model_;

  public:
    ModelRenderer(const Model& model);

    void render(const Transform& transform, Shader& shader,
                const RenderingEngine& rendering_engine) override;
};

} // namespace SGE
#endif
