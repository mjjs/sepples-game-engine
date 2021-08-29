#include "scenehierarchypanel.h"

#include "engine/ecs/components/tagcomponent.h"
#include "engine/ecs/gameobject.h"
#include "engine/ecs/scene.h"

#include <imgui.h>
#include <memory>

namespace SGE
{

SceneHierarchyPanel::SceneHierarchyPanel(const std::shared_ptr<Scene>& scene)
    : scene_{scene}
{
}

void SceneHierarchyPanel::render_imgui()
{
    ImGui::Begin("Scene Hierarchy");

    auto view = scene_->components_.view<TagComponent>();
    for (const auto game_object_id : view) {
        draw_game_object_node(GameObject{game_object_id, scene_.get()});
    }

    ImGui::End();
}

void SceneHierarchyPanel::draw_game_object_node(GameObject game_object)
{
    const auto& tag = game_object.get_component<TagComponent>().tag();

    ImGuiTreeNodeFlags flags =
        ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

    if (selected_game_object_ == game_object) {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    bool is_open = ImGui::TreeNodeEx(tag.c_str(), flags, "%s", tag.c_str());
    if (ImGui::IsItemClicked()) {
        selected_game_object_ = game_object;
    }

    if (is_open) {
        ImGui::TreePop();
    }
}

} // namespace SGE
