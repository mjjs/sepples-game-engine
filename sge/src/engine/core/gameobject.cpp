#include "engine/components/camera.h"
#include "engine/components/gamecomponent.h"
#include "engine/core/gameobject.h"
#include "engine/rendering/renderingengine.h"
#include "engine/core/input.h"
#include "engine/rendering/shader.h"
#include "engine/core/transform.h"

#include <memory>

namespace SGE {

void GameObject::add_component(std::shared_ptr<GameComponent> component)
{
    components_.push_back(component);
    component->set_parent(this);
}

void GameObject::update(const float delta)
{
    for (const auto& component : components_) {
        component->update(delta);
    }

    for (const auto& child : children_) {
        child->update(delta);
    }
}

void GameObject::fixed_update()
{
    for (const auto& component : components_) {
        component->fixed_update(transform_);
    }

    for (const auto& child : children_) {
        child->fixed_update();
    }
}

void GameObject::render(Shader& shader, const RenderingEngine& rendering_engine)
{
    for (const auto& component : components_) {
        component->render(transform_, shader, rendering_engine);
    }

    for (const auto& child : children_) {
        child->render(shader, rendering_engine);
    }
}

void GameObject::add_to_rendering_engine(RenderingEngine& rendering_engine) const
{
    for (const auto& component : components_) {
        component->add_to_rendering_engine(rendering_engine);
    }

    for (const auto& child : children_) {
        child->add_to_rendering_engine(rendering_engine);
    }
}

void GameObject::add_child(std::shared_ptr<GameObject> child)
{
    child->transform().set_parent(&transform_);
    children_.push_back(child);
}

void GameObject::set_transform(const Transform& transform)
{
    transform_ = transform;
}

Transform& GameObject::transform()
{
    return transform_;
}

} // namespace SGE
