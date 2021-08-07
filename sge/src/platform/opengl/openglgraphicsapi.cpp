#include "platform/opengl/openglgraphicsapi.h"

#include "engine/math/vector3.h"

#include <glad/glad.h>

namespace SGE
{

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

void OpenGLGraphicsAPI::set_viewport(unsigned int width, unsigned int height)
{
    glViewport(0, 0, width, height);
}

} // namespace SGE
