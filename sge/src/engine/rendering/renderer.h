#ifndef _SGE_RENDERER_H
#define _SGE_RENDERER_H

#include "engine/rendering/buffers/uniformbuffer.h"
#include "engine/rendering/graphicsapi.h"
#include "engine/rendering/shader.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace SGE
{

class Game;
class Camera;
class Mesh;
class Model;
class Transform;

class Renderer
{
    friend class Game;

  private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static std::unique_ptr<GraphicsAPI> graphics_api_;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static std::shared_ptr<UniformBuffer> camera_buffer_;

    static void set_viewport(unsigned int x, unsigned int y, unsigned int width,
                             unsigned int height);

  public:
    static void init();
    static void clear_screen();
    static void set_clear_colour(const glm::vec4& colour);

    static void prepare_frame(const Camera& camera,
                              const glm::mat4& view_matrix);
    static void submit(const std::shared_ptr<Shader>& shader,
                       const std::shared_ptr<Model>& model,
                       const Transform& transform);

    static void submit(const std::shared_ptr<Shader>& shader,
                       const std::shared_ptr<Mesh>& mesh,
                       const Transform& transform);
};

} // namespace SGE
#endif
