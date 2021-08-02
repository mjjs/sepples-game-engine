#ifndef _SGE_OPENGL_GRAPHICSAPI_H
#define _SGE_OPENGL_GRAPHICSAPI_H

#include "graphicsapi.h"
#include "vector3.h"

namespace SGE {

class OpenGLGraphicsAPI : public GraphicsAPI {
    private:
        Vector3 clear_colour_;

    public:
        void clear_screen() override;
        void set_clear_colour(const Vector3& colour) override;
};

} // namespace SGE
#endif
