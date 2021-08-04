#ifndef _SGE_RENDERINGENGINE_H
#define _SGE_RENDERINGENGINE_H

#include "gameobject.h"
#include "graphicsapi.h"
#include "light.h"
#include "sgemath.h"
#include "uniformbuffer.h"
#include "vector3.h"

#include <memory>
#include <vector>

namespace SGE
{

class Camera;
class Mesh;
class Model;
class Transform;

class RenderingEngine
{
  private:
    Camera* main_camera_ = nullptr;

    std::vector<Light*> lights_{};
    Light* active_light_ = nullptr;

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static std::unique_ptr<GraphicsAPI> graphics_api_;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static std::shared_ptr<UniformBuffer> camera_buffer_;

  public:
    static void init();
    static void clear_screen();
    static void set_clear_colour(const Vector3& colour);

    static void prepare_frame(const Camera& camera);
    static void submit(const std::shared_ptr<Shader>& shader,
                       const std::shared_ptr<Model>& model,
                       const Transform& transform);

    static void submit(const std::shared_ptr<Shader>& shader, const Mesh& mesh,
                       const Transform& transform);

    // OLD API

    void render(GameObject& gameobject);

    void set_camera(Camera* camera);
    Camera* camera() const;
    Light* active_light() const;
    void add_light(Light* light);
};

} // namespace SGE
#endif
