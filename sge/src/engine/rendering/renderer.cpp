#include "engine/rendering/renderer.h"

#include "engine/debug/profiler.h"
#include "engine/math/matrix4.h"
#include "engine/math/vector3.h"
#include "engine/rendering/buffers/uniformbuffer.h"
#include "engine/rendering/camera.h"
#include "engine/rendering/mesh.h"
#include "engine/rendering/model.h"
#include "engine/rendering/shader.h"

#include <memory>

namespace SGE
{

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::unique_ptr<GraphicsAPI> Renderer::graphics_api_ = GraphicsAPI::create();

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::shared_ptr<UniformBuffer> Renderer::camera_buffer_;

void Renderer::init()
{
    camera_buffer_ = UniformBuffer::create(sizeof(Matrix4), 0);
}

void Renderer::clear_screen()
{
    graphics_api_->clear_screen();
}

void Renderer::set_clear_colour(const Vector3& colour)
{
    graphics_api_->set_clear_colour(colour);
}

void Renderer::prepare_frame(const Camera& camera)
{
    SGE_PROFILE_FUNCTION();

    auto view_projection = camera.get_view_projection();
    camera_buffer_->set_data(view_projection[0].data(),
                             sizeof(view_projection));
}

void Renderer::submit(const std::shared_ptr<Shader>& shader,
                      const std::shared_ptr<Model>& model,
                      const Transform& transform)
{
    SGE_PROFILE_FUNCTION();

    shader->bind();

    for (const auto& mesh : model->meshes()) {
        submit(shader, mesh, transform);
    }
}

void Renderer::submit(const std::shared_ptr<Shader>& shader,
                      const std::shared_ptr<Mesh>& mesh,
                      const Transform& transform)
{
    SGE_PROFILE_FUNCTION();

    shader->bind();
    shader->set_uniform("transform_u", transform.get_transformation());

    const auto material = mesh->material();

    mesh->draw(*shader);
}

void Renderer::set_viewport(const unsigned int x, const unsigned int y,
                            const unsigned int width, const unsigned int height)
{
    graphics_api_->set_viewport(x, y, width, height);
}

} // namespace SGE
