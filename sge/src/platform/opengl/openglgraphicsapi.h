#ifndef _SGE_OPENGL_GRAPHICSAPI_H
#define _SGE_OPENGL_GRAPHICSAPI_H

#include "engine/rendering/graphicsapi.h"
#include "engine/math/vector3.h"

namespace SGE
{

class OpenGLGraphicsAPI : public GraphicsAPI
{
  private:
    Vector3 clear_colour_;

  public:
    void clear_screen() override;
    void set_clear_colour(const Vector3& colour) override;
};

} // namespace SGE
#endif
