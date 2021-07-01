#include "camera.h"
#include "gamecomponent.h"
#include "gameobject.h"
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
}

void SGE::GameObject::input(const Input& input)
{
    for (const auto& component : components_) {
        component->input(input, transform_);
    }

    for (const auto& child : children_) {
        child->input(input);
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

void SGE::GameObject::render(Shader& shader, const Camera& camera)
{
    for (const auto& component : components_) {
        component->render(transform_, shader, camera);
    }

    for (const auto& child : children_) {
        child->render(shader, camera);
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
