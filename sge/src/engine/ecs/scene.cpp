#include "engine/ecs/scene.h"

#include "engine/ecs/components/cameracomponent.h"
#include "engine/ecs/components/cppscriptcomponent.h"
#include "engine/ecs/components/meshrenderercomponent.h"
#include "engine/ecs/components/modelrenderercomponent.h"
#include "engine/ecs/components/tagcomponent.h"
#include "engine/ecs/components/transformcomponent.h"
#include "engine/ecs/gameobject.h"
#include "engine/rendering/renderer.h"

#include <cstdint>

namespace SGE
{

void Scene::update(float delta)
{
    script_update(delta);

    // TODO: Make sure there is only one camera
    // (or better, support multiple cameras and have a MAIN camera)
    auto group = components_.group<CameraComponent, TransformComponent>();
    for (const auto game_object : group) {
        auto [camera, transform] =
            group.get<CameraComponent, TransformComponent>(game_object);
        Renderer::prepare_frame(camera.camera(),
                                transform.transform().get_transformation());
    }

    auto meshes = components_.view<MeshRendererComponent, TransformComponent>();

    for (const auto game_object : meshes) {
        auto [mesh_component, transform_component] =
            meshes.get<MeshRendererComponent, TransformComponent>(game_object);

        Renderer::submit(shader_, mesh_component.mesh(),
                         transform_component.transform());
    }

    auto models =
        components_.view<ModelRendererComponent, TransformComponent>();

    for (const auto game_object : models) {
        auto [model_component, transform_component] =
            models.get<ModelRendererComponent, TransformComponent>(game_object);

        Renderer::submit(shader_, model_component.model(),
                         transform_component.transform());
    }
}

void Scene::fixed_update()
{
    script_fixed_update();
}

void Scene::on_window_resized(const std::uint32_t width,
                              const std::uint32_t height)
{
    auto cameras = components_.view<CameraComponent>();
    for (const auto& game_object : cameras) {
        auto& camera = cameras.get<CameraComponent>(game_object);
        camera.camera().update_aspect_ratio(width, height);
    }
}

GameObject Scene::add_game_object(const std::string& tag)
{
    auto game_object = GameObject{components_.create(), this};

    game_object.add_component<TagComponent>(get_unique_name(tag));
    game_object.add_component<TransformComponent>();

    return game_object;
}

void Scene::remove_game_object(GameObject game_object)
{
    components_.destroy(game_object);
}

void Scene::script_update(const float delta)
{
    auto scriptables = components_.view<CPPScriptComponent>();

    scriptables.each([=](auto entity, auto& script) {
        if (!script.instance) {
            script.instance               = script.instantiate_script();
            script.instance->game_object_ = GameObject{entity, this};

            script.instance->on_create();
        }

        script.instance->update(delta);
    });
}

void Scene::script_fixed_update()
{
    auto scriptables = components_.view<CPPScriptComponent>();

    scriptables.each([=](auto entity, auto& script) {
        if (!script.instance) {
            script.instance               = script.instantiate_script();
            script.instance->game_object_ = GameObject{entity, this};

            script.instance->on_create();
        }

        script.instance->fixed_update();
    });
}

std::string Scene::get_unique_name(const std::string& name)
{
    std::uint32_t index = 1;

    if (!reserved_names_.contains(name)) {
        reserved_names_[name] = index;
        return name;
    }

    index                 = reserved_names_[name];
    reserved_names_[name] = index + 1;

    return name + "_" + std::to_string(index);
}

} // namespace SGE
