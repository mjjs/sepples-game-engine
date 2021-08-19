#ifndef _SGE_RENDERER_2D_H
#define _SGE_RENDERER_2D_H

#include "engine/rendering/graphicsapi.h"

#include <glm/glm.hpp>
#include <memory>

namespace SGE
{

class Camera;
class Transform;
class Texture;

class Renderer2D
{
    friend class Game;

  private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static std::unique_ptr<GraphicsAPI> graphics_api_;

    static void initialize_batch();
    static void end_batch();
    static void execute_batch();
    static void init();

    static void draw_quad(const Transform& transform, const glm::vec4& colour,
                          const std::shared_ptr<Texture>& texture);

  public:
    static void prepare_frame(const Camera& camera);
    static void end_frame();

    static void draw_quad(const Transform& transform, const glm::vec4& colour);
    static void draw_quad(const Transform& transform,
                          const std::shared_ptr<Texture>& texture);
};

} // namespace SGE

#endif
