#ifndef _TESTGAME_MODELRENDERER_H
#define _TESTGAME_MODELRENDERER_H

#include "camera.h"
#include "basicshader.h"
#include "gamecomponent.h"
#include "mesh.h"
#include "model.h"
#include "transform.h"
#include "input.h"
#include "shader.h"
#include "renderingengine.h"

namespace SGE {

class ModelRenderer : public GameComponent {
    private:
        Model model_;

    public:
        ModelRenderer(const Model& model);

        void render(const Transform& transform, Shader& shader, const RenderingEngine& rendering_engine) override;
};

} // namespace SGE
#endif
