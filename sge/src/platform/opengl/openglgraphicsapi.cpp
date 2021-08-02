#include "openglgraphicsapi.h"
#include "vector3.h"

#include <glad/glad.h>

namespace SGE {

void OpenGLGraphicsAPI::clear_screen()
{
    auto [r, g, b] = clear_colour_;
    glClearColor(r, g, b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLGraphicsAPI::set_clear_colour(const Vector3& colour)
{
    clear_colour_ = colour;
}

} // namespace SGE
