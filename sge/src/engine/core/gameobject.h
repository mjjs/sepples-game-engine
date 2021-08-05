#ifndef _SGE_GAMEOBJECT_H
#define _SGE_GAMEOBJECT_H

#include "engine/components/camera.h"
#include "engine/components/gamecomponent.h"
#include "engine/core/input.h"
#include "engine/rendering/shader.h"
#include "engine/core/transform.h"

#include <memory>
#include <vector>

namespace SGE
{
class RenderingEngine;

class GameObject
{
  private:
    Transform transform_{};
    std::vector<std::shared_ptr<GameObject>> children_{};
    std::vector<std::shared_ptr<GameComponent>> components_{};

  public:
    GameObject()                  = default;
    GameObject(const GameObject&) = default;
    GameObject(GameObject&&)      = default;
    GameObject& operator=(const GameObject&) = default;
    GameObject& operator=(GameObject&&) = default;
    virtual ~GameObject()               = default;

    virtual void update(float delta);
    virtual void fixed_update();
    virtual void render(Shader& shader,
                        const RenderingEngine& rendering_engine);
    virtual void
    add_to_rendering_engine(RenderingEngine& rendering_engine) const;

    void add_child(std::shared_ptr<GameObject> child);
    void add_component(std::shared_ptr<GameComponent> component);
    void set_transform(const Transform& transform);
    Transform& transform();
};

} // namespace SGE
#endif
