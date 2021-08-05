#include "engine/rendering/renderingengine.h"

#include "engine/components/camera.h"
#include "engine/math/matrix4.h"
#include "engine/rendering/mesh.h"
#include "engine/rendering/model.h"
#include "engine/rendering/shaders/shader.h"
#include "engine/rendering/buffers/uniformbuffer.h"
#include "engine/math/vector3.h"

#include <memory>

namespace SGE
{

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::unique_ptr<GraphicsAPI> RenderingEngine::graphics_api_ =
    GraphicsAPI::create();

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::shared_ptr<UniformBuffer> RenderingEngine::camera_buffer_;

void RenderingEngine::init()
{
    camera_buffer_ = UniformBuffer::create(sizeof(Matrix4), 0);
}

void RenderingEngine::clear_screen()
{
    graphics_api_->clear_screen();
}

void RenderingEngine::set_clear_colour(const Vector3& colour)
{
    graphics_api_->set_clear_colour(colour);
}

void RenderingEngine::prepare_frame(const Camera& camera)
{
    auto view_projection = camera.get_view_projection();
    camera_buffer_->set_data(view_projection[0].data(),
                             sizeof(view_projection));
}

void RenderingEngine::submit(const std::shared_ptr<Shader>& shader,
                             const std::shared_ptr<Model>& model,
                             const Transform& transform)
{
    shader->bind();

    for (const auto& mesh : model->meshes()) {
        submit(shader, mesh, transform);
    }
}

void RenderingEngine::submit(const std::shared_ptr<Shader>& shader,
                             const std::shared_ptr<Mesh>& mesh,
                             const Transform& transform)
{
    shader->bind();
    shader->set_uniform("transform_u", transform.get_transformation());

    const auto material = mesh->material();

    mesh->draw(*shader);
}

} // namespace SGE