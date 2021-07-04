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

class ModelRenderer : public SGE::GameComponent {
    private:
        Model model_;

    public:
        ModelRenderer(const Model& model);

        void render(const Math::Transform& transform, Shader& shader, const Camera& camera) override;
};
#endif
