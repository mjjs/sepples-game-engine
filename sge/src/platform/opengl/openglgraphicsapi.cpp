#include "platform/opengl/openglgraphicsapi.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace SGE
{

void OpenGLGraphicsAPI::clear_screen()
{
    glClearColor(clear_colour_.r, clear_colour_.g, clear_colour_.b,
                 clear_colour_.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLGraphicsAPI::set_clear_colour(const glm::vec4& colour)
{
    clear_colour_ = colour;
}

void OpenGLGraphicsAPI::set_viewport(unsigned int x, unsigned int y,
                                     unsigned int width, unsigned int height)
{
    glViewport(x, y, width, height);
}

void OpenGLGraphicsAPI::draw_indexed(
    const std::shared_ptr<VertexArray>& vertex_array)
{
    glDrawElements(GL_TRIANGLES, vertex_array->index_buffer()->count(),
                   GL_UNSIGNED_INT, nullptr);
}

} // namespace SGE
