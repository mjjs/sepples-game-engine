#ifndef _SGE_LIGHT_H
#define _SGE_LIGHT_H

#include "gamecomponent.h"
#include "shader.h"
#include "vector3.h"

#include <memory>

namespace SGE {
class RenderingEngine;

class Light : public GameComponent {
    private:
        Vector3 colour_{1.0F, 1.0F, 1.0F};
        float intensity_ = 1.0F;
        std::shared_ptr<Shader> shader_;

    public:
        Light(std::shared_ptr<Shader> shader);
        explicit Light(
            std::shared_ptr<Shader> shader,
            const Vector3& colour,
            float intensity
        );

        float intensity() const;
        const Vector3& colour() const;
        std::shared_ptr<Shader> shader() const;
        void add_to_rendering_engine(RenderingEngine& rendering_engine) override;
};
} // namespace SGE

#endif