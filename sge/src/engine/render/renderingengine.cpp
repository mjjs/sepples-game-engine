#include "renderingengine.h"

#include "camera.h"
#include "matrix4.h"
#include "mesh.h"
#include "model.h"
#include "shader.h"
#include "uniformbuffer.h"
#include "vector3.h"

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

    shader->set_uniform("material_u.ambient", material.ambient_colour());
    shader->set_uniform("material_u.diffuse", material.diffuse_colour());
    shader->set_uniform("material_u.specular", material.specular_colour());
    shader->set_uniform("material_u.shininess", material.shininess());

    mesh->draw(*shader);
}

} // namespace SGE
