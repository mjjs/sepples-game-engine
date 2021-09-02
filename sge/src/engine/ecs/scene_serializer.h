#ifndef _SGE_SCENE_SERIALIZER_H
#define _SGE_SCENE_SERIALIZER_H

#include "gameobject.h"
#include "scene.h"

#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>
#include <string>
#include <yaml-cpp/yaml.h>

namespace SGE
{

class SceneSerializer
{
  private:
    static void serialize_headers(YAML::Emitter& out);
    static void serialize_game_object(YAML::Emitter& out,
                                      GameObject game_object);
    static void serialize_scene(YAML::Emitter& out,
                                const std::shared_ptr<Scene>& scene);

  public:
    static void serialize_yaml(const std::shared_ptr<Scene>& scene,
                               const std::string& filepath);
    static void deserialize_yaml(const std::shared_ptr<Scene>& scene,
                                 const std::string& filepath);
};

class SceneSerializationFailedException : public std::exception
{
  private:
    std::string message_;

  public:
    SceneSerializationFailedException(const std::string& message)
        : message_{message}
    {
    }

    const char* what() const noexcept override
    {
        return message_.c_str();
    }
};

} // namespace SGE

template <>
struct YAML::convert<glm::vec3> {
    static YAML::Node encode(const glm::vec3& rhs)
    {
        YAML::Node node;

        node.push_back(rhs.x);
        node.push_back(rhs.y);
        node.push_back(rhs.z);

        return node;
    }

    static bool decode(const Node& node, glm::vec3& rhs)
    {
        if (!node.IsSequence() || node.size() != 3) {
            return false;
        }

        rhs.x = node[0].as<float>();
        rhs.y = node[1].as<float>();
        rhs.z = node[2].as<float>();

        return true;
    }
};

template <>
struct YAML::convert<glm::vec4> {
    static YAML::Node encode(const glm::vec4& rhs)
    {
        YAML::Node node;

        node.push_back(rhs.x);
        node.push_back(rhs.y);
        node.push_back(rhs.z);
        node.push_back(rhs.w);

        return node;
    }

    static bool decode(const Node& node, glm::vec4& rhs)
    {
        if (!node.IsSequence() || node.size() != 4) {
            return false;
        }

        rhs.x = node[0].as<float>();
        rhs.y = node[1].as<float>();
        rhs.z = node[2].as<float>();
        rhs.w = node[3].as<float>();

        return true;
    }
};

template <>
struct YAML::convert<glm::quat> {
    static YAML::Node encode(const glm::quat& rhs)
    {
        YAML::Node node;

        node.push_back(rhs.x);
        node.push_back(rhs.y);
        node.push_back(rhs.z);
        node.push_back(rhs.w);

        return node;
    }

    static bool decode(const Node& node, glm::quat& rhs)
    {
        if (!node.IsSequence() || node.size() != 4) {
            return false;
        }

        rhs.x = node[0].as<float>();
        rhs.y = node[1].as<float>();
        rhs.z = node[2].as<float>();
        rhs.w = node[3].as<float>();

        return true;
    }
};

#endif
