#ifndef _SGE_OPENGL_GRAPHICSAPI_H
#define _SGE_OPENGL_GRAPHICSAPI_H

#include "engine/rendering/graphicsapi.h"

#include <glm/glm.hpp>

namespace SGE
{

class OpenGLGraphicsAPI : public GraphicsAPI
{
  private:
    glm::vec4 clear_colour_;

  public:
    void clear_screen() override;
    void set_clear_colour(const glm::vec4& colour) override;
    void set_viewport(unsigned int x, unsigned int y, unsigned int width,
                      unsigned int height) override;
};

} // namespace SGE
#endif
