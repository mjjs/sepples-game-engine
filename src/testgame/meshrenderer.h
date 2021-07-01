#ifndef _TESTGAME_MESHRENDERER_H
#define _TESTGAME_MESHRENDERER_H

#include "camera.h"
#include "gamecomponent.h"
#include "material.h"
#include "mesh.h"
#include "basicshader.h"
#include "transform.h"
#include "shader.h"

class MeshRenderer : public SGE::GameComponent {
    private:
        Mesh mesh_;
        Material material_;

    public:
        MeshRenderer(const Mesh& mesh, const Material& material);

        void init() override;
        void input(const Input& input, const Math::Transform& transform) override;
        void update(const Math::Transform& transform) override;
        void render(const Math::Transform& transform, Shader& shader, const Camera& camera) override;
};
#endif
