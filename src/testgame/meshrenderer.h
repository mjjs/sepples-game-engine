#ifndef _TESTGAME_MESHRENDERER_H
#define _TESTGAME_MESHRENDERER_H
#include "gamecomponent.h"
#include "material.h"
#include "mesh.h"
#include "basicshader.h"
#include "transform.h"

class MeshRenderer : public SGE::GameComponent {
    private:
        Mesh mesh_;
        Material material_;
        BasicShader shader_;

    public:
        MeshRenderer(const Mesh& mesh, const Material& material);

        void init() override;
        void render(const Math::Transform& transform) override;
        void input(const Math::Transform& transform) override;
        void update(const Math::Transform& transform) override;
};
#endif
