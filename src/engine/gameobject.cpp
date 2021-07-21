#include "camera.h"
#include "gamecomponent.h"
#include "gameobject.h"
#include "renderingengine.h"
#include "input.h"
#include "shader.h"
#include "transform.h"

#include <memory>

namespace SGE {

void GameObject::add_child(std::shared_ptr<GameObject> child)
{
    children_.push_back(child);
}

void GameObject::add_component(std::shared_ptr<GameComponent> component)
{
    components_.push_back(component);
    component->set_parent(this);
}

void GameObject::update(const float delta)
{
    for (const auto& component : components_) {
        component->update(transform_, delta);
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

void GameObject::set_transform(const Math::Transform& transform)
{
    transform_ = transform;
}

Math::Transform& GameObject::transform()
{
    return transform_;
}

} // namespace SGE
