#ifndef _TESTGAME_MODELRENDERER_H
#define _TESTGAME_MODELRENDERER_H

#include "basicshader.h"
#include "camera.h"
#include "gamecomponent.h"
#include "input.h"
#include "mesh.h"
#include "model.h"
#include "renderingengine.h"
#include "shader.h"
#include "transform.h"

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
