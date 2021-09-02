#include "scene_serializer.h"

#include "engine/ecs/components/cameracomponent.h"
#include "engine/ecs/components/tagcomponent.h"
#include "engine/ecs/components/transformcomponent.h"
#include "gameobject.h"
#include "scene.h"

#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>

namespace SGE
{

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
    return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
    return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::quat& q)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << q.x << q.y << q.z << q.w << YAML::EndSeq;
    return out;
}

void SceneSerializer::serialize_headers(YAML::Emitter& out)
{
    out << YAML::Comment("SGE Scene");
}

void SceneSerializer::serialize_game_object(YAML::Emitter& out,
                                            GameObject game_object)
{
    out << YAML::BeginMap;

    out << YAML::Key << "GameObject" << YAML::Value << "<insert uuid here>";

    if (game_object.has_component<TagComponent>()) {
        out << YAML::Key << "TagComponent" << YAML::Value << YAML::BeginMap;

        auto& tag = game_object.get_component<TagComponent>().tag();
        out << YAML::Key << "Tag" << YAML::Value << tag;

        out << YAML::EndMap;
    }

    if (game_object.has_component<TransformComponent>()) {
        out << YAML::Key << "TransformComponent" << YAML::Value
            << YAML::BeginMap;

        auto& transform =
            game_object.get_component<TransformComponent>().transform();
        out << YAML::Key << "Position" << YAML::Value << transform.position();
        out << YAML::Key << "Rotation" << YAML::Value << transform.rotation();
        out << YAML::Key << "Scale" << YAML::Value << transform.scale();
        out << YAML::Key << "EulerHints" << YAML::Value
            << transform.rotation_euler_hints();

        out << YAML::EndMap;
    }

    if (game_object.has_component<CameraComponent>()) {
        out << YAML::Key << "CameraComponent" << YAML::Value << YAML::BeginMap;

        auto& camera = game_object.get_component<CameraComponent>().camera();

        out << YAML::Key << "ProjectionType";
        out << YAML::Value << static_cast<int>(camera.projection_type());

        out << YAML::Key << "Fov" << YAML::Value << camera.fov();

        out << YAML::Key << "AspectRatio";
        out << YAML::Value << camera.aspect_ratio();

        out << YAML::Key << "PerspectiveNear";
        out << YAML::Value << camera.perspective_z_near();

        out << YAML::Key << "PerspectiveFar";
        out << YAML::Value << camera.perspective_z_near();

        out << YAML::Key << "OrthographicSize";
        out << YAML::Value << camera.orthographic_size();

        out << YAML::Key << "OrthographicNear";
        out << YAML::Value << camera.orthographic_z_near();

        out << YAML::Key << "OrthographicFar";
        out << YAML::Value << camera.orthographic_z_near();

        out << YAML::EndMap;
    }

    out << YAML::EndMap;
}

void SceneSerializer::serialize_scene(YAML::Emitter& out,
                                      const std::shared_ptr<Scene>& scene)
{
    out << YAML::BeginMap;
    out << YAML::Key << "Scene" << YAML::Value << YAML::BeginMap;

    out << YAML::Key << "Name" << YAML::Value << "Scene Name";
    out << YAML::Key << "GameObjects" << YAML::Value << YAML::BeginSeq;

    scene->components_.each([&](auto game_object_id) {
        GameObject game_object{game_object_id, scene.get()};
        if (!game_object) {
            return;
        }

        serialize_game_object(out, game_object);
    });

    out << YAML::EndSeq << YAML::EndMap;
    out << YAML::EndMap;
}

void SceneSerializer::serialize_yaml(const std::shared_ptr<Scene>& scene,
                                     const std::string& filepath)
{
    YAML::Emitter out;
    serialize_headers(out);
    serialize_scene(out, scene);

    auto directory = std::filesystem::path{filepath}.remove_filename();

    std::filesystem::create_directories(directory);

    std::ofstream file(filepath);
    file << out.c_str();
}

void SceneSerializer::deserialize_yaml(const std::shared_ptr<Scene>& scene,
                                       const std::string& filepath)
{
    YAML::Node yaml = YAML::LoadFile(filepath);
    if (!yaml["Scene"]) {
        throw SceneSerializationFailedException{
            "Scene node is missing from yaml file."};
    }

    const auto scene_yaml = yaml["Scene"];

    // TODO: implement name into scene class
    const auto scene_name = scene_yaml["Name"].as<std::string>();

    if (const auto& game_objects = scene_yaml["GameObjects"]) {
        for (const auto& field : game_objects) {
            const auto game_object_id = field["GameObject"].as<std::string>();

            std::string tag{};
            if (const auto& tag_field = field["TagComponent"]) {
                tag = tag_field["Tag"].as<std::string>();
            }

            auto game_object = scene->add_game_object(tag);

            if (const auto& transform_component_field =
                    field["TransformComponent"]) {
                auto& transform =
                    game_object.get_component<TransformComponent>().transform();

                transform.set_position(
                    transform_component_field["Position"].as<glm::vec3>());
                transform.set_rotation(
                    transform_component_field["Rotation"].as<glm::quat>());
                transform.set_scale(
                    transform_component_field["Scale"].as<glm::vec3>());
                transform.set_rotation_euler_hints(
                    transform_component_field["EulerHints"].as<glm::vec3>());
            }

            if (const auto& camera_component_field = field["CameraComponent"]) {
                auto& camera =
                    game_object.add_component<CameraComponent>().camera();

                camera.set_projection_type(static_cast<Camera::ProjectionType>(
                    camera_component_field["ProjectionType"].as<int>()));

                camera.set_fov(camera_component_field["Fov"].as<float>());
                camera.set_aspect_ratio(
                    camera_component_field["AspectRatio"].as<float>());
                camera.set_perspective_z_near(
                    camera_component_field["PerspectiveNear"].as<float>());
                camera.set_perspective_z_far(
                    camera_component_field["PerspectiveFar"].as<float>());
                camera.set_orthographic_size(
                    camera_component_field["OrthographicSize"].as<float>());
                camera.set_orthographic_z_near(
                    camera_component_field["OrthographicNear"].as<float>());
                camera.set_orthographic_z_far(
                    camera_component_field["OrthographicFar"].as<float>());
            }
        }
    }
}

} // namespace SGE
