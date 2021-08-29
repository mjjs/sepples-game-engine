#include "gameobjectpropertiespanel.h"

#include "engine/ecs/components/tagcomponent.h"
#include "engine/ecs/components/transformcomponent.h"
#include "engine/ecs/gameobject.h"

#include <array>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <string.h>

namespace SGE
{

void GameObjectPropertiesPanel::render_imgui()
{
    ImGui::Begin("Game object properties");
    ImGui::End();
}

void GameObjectPropertiesPanel::render_imgui(GameObject game_object)
{
    ImGui::Begin("Game object properties");
    draw_components(game_object);
    ImGui::End();
}

void GameObjectPropertiesPanel::draw_components(GameObject game_object)
{
    if (game_object.has_component<TagComponent>()) {
        auto& tag = game_object.get_component<TagComponent>().tag();

        auto buffer = std::array<char, 256>{};
        tag.copy(buffer.data(), tag.size());
        buffer[255] = '\0';

        if (ImGui::InputText("Tag", buffer.data(), sizeof(buffer))) {
            tag = std::string(buffer.data());
        }
    }

    if (game_object.has_component<TransformComponent>()) {
        if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen,
                              "Transform")) {
            auto& transform =
                game_object.get_component<TransformComponent>().transform();

            ImGui::DragFloat3("Position", glm::value_ptr(transform.position()),
                              0.1F);

            ImGui::TreePop();
        }
    }
}

} // namespace SGE
