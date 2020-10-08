#include "gamecomponent.h"
#include "gameobject.h"

#include "transform.h"

#include <memory>

void SGE::GameObject::add_child(std::shared_ptr<GameObject> child)
{
    children_.push_back(child);
}

void SGE::GameObject::add_component(std::shared_ptr<GameComponent> component)
{
    components_.push_back(component);
}

void SGE::GameObject::input()
{
    for (const auto& component : components_) {
        component->input(transform_);
    }

    for (const auto& child : children_) {
        child->input();
    }
}

void SGE::GameObject::update()
{
    for (const auto& component : components_) {
        component->update(transform_);
    }

    for (const auto& child : children_) {
        child->update();
    }
}

void SGE::GameObject::render()
{
    for (const auto& component : components_) {
        component->render(transform_);
    }

    for (const auto& child : children_) {
        child->render();
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
