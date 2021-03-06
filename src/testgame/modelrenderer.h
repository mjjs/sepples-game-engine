#ifndef _TESTGAME_MODELRENDERER_H
#define _TESTGAME_MODELRENDERER_H
#include "basicshader.h"
#include "gamecomponent.h"
#include "mesh.h"
#include "model.h"
#include "transform.h"

class ModelRenderer : public SGE::GameComponent {
    private:
        Model model_;
        BasicShader shader_;

    public:
        ModelRenderer(const Model& model);

        void init() override;
        void render(const Math::Transform& transform) override;
        void input(const Math::Transform& transform) override;
        void update(const Math::Transform& transform) override;
};
#endif
