#include "camera.h"
#include "gamecomponent.h"
#include "gameobject.h"
#include "renderingengine.h"
#include "input.h"
#include "shader.h"
#include "transform.h"

#include <memory>

void SGE::GameObject::add_child(std::shared_ptr<GameObject> child)
{
    children_.push_back(child);
}

void SGE::GameObject::add_component(std::shared_ptr<GameComponent> component)
{
    components_.push_back(component);
    component->set_parent(this);
}

void SGE::GameObject::update(const float delta)
{
    for (const auto& component : components_) {
        component->update(transform_, delta);
    }

    for (const auto& child : children_) {
        child->update(delta);
    }
}

void SGE::GameObject::fixed_update()
{
    for (const auto& component : components_) {
        component->fixed_update(transform_);
    }

    for (const auto& child : children_) {
        child->fixed_update();
    }
}

void SGE::GameObject::render(Shader& shader, const SGE::RenderingEngine& rendering_engine)
{
    for (const auto& component : components_) {
        component->render(transform_, shader, rendering_engine);
    }

    for (const auto& child : children_) {
        child->render(shader, rendering_engine);
    }
}

void SGE::GameObject::add_to_rendering_engine(SGE::RenderingEngine& rendering_engine) const
{
    for (const auto& component : components_) {
        component->add_to_rendering_engine(rendering_engine);
    }

    for (const auto& child : children_) {
        child->add_to_rendering_engine(rendering_engine);
    }
}

void SGE::GameObject::set_transform(const Math::Transform& transform)
{
    transform_ = transform;
}

Math::Transform& SGE::GameObject::transform()
{
    return transform_;
}
