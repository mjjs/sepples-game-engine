#ifndef _SGE_MESHRENDERER_H
#define _SGE_MESHRENDERER_H

#include "camera.h"
#include "gamecomponent.h"
#include "material.h"
#include "mesh.h"
#include "basicshader.h"
#include "transform.h"
#include "shader.h"
#include "renderingengine.h"

#include <memory>

namespace SGE {

class MeshRenderer : public GameComponent {
    private:
        std::shared_ptr<Mesh> mesh_;

    public:
        MeshRenderer(std::shared_ptr<Mesh>& mesh);

        void render(const Transform& transform, Shader& shader, const RenderingEngine& rendering_engine) override;
};

} // namespace SGE
#endif
