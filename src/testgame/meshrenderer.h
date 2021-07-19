#ifndef _TESTGAME_MESHRENDERER_H
#define _TESTGAME_MESHRENDERER_H

#include "camera.h"
#include "gamecomponent.h"
#include "material.h"
#include "mesh.h"
#include "basicshader.h"
#include "transform.h"
#include "shader.h"
#include "renderingengine.h"

#include <memory>

class MeshRenderer : public SGE::GameComponent {
    private:
        std::unique_ptr<Mesh> mesh_;

    public:
        MeshRenderer(std::unique_ptr<Mesh>& mesh);

        void render(const Math::Transform& transform, Shader& shader, const SGE::RenderingEngine& rendering_engine) override;
};
#endif
