#include "gameobjectpropertiespanel.h"

#include "engine/ecs/components/cameracomponent.h"
#include "engine/ecs/components/tagcomponent.h"
#include "engine/ecs/components/transformcomponent.h"
#include "engine/ecs/gameobject.h"

#include <array>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <string.h>

namespace SGE
{

static constexpr auto ADD_COMPONENT_POPUP_ID = "add component popup";

void GameObjectPropertiesPanel::render_imgui()
{
    ImGui::Begin("Game object properties");
    if (auto game_object = scene_hierarchy_panel_->selected_game_object()) {
        draw_components(game_object);
    }
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
        if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
            auto& transform =
                game_object.get_component<TransformComponent>().transform();

            ImGui::DragFloat3("Position", glm::value_ptr(transform.position()),
                              0.1F);

            auto& rotation_eulers = transform.rotation_euler_hints();

            if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation_eulers),
                                  1.0F)) {
                transform.set_rotation(rotation_eulers);
            }

            ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale()), 0.1F);

            ImGui::TreePop();
        }
    }

    if (game_object.has_component<CameraComponent>()) {
        if (ImGui::TreeNodeEx("Camera", ImGuiTreeNodeFlags_DefaultOpen)) {
            auto& camera =
                game_object.get_component<CameraComponent>().camera();

            const auto projection_type = camera.projection_type();

            const char* projection_type_str =
                projection_type == Camera::ProjectionType::PERSPECTIVE
                    ? "Perspective"
                    : "Orthographic";

            if (ImGui::BeginCombo("Projection", projection_type_str)) {
                if (ImGui::Selectable(
                        "Perspective",
                        camera.projection_type() ==
                            Camera::ProjectionType::PERSPECTIVE)) {
                    camera.set_projection_type(
                        Camera::ProjectionType::PERSPECTIVE);
                }

                if (camera.projection_type() ==
                    Camera::ProjectionType::PERSPECTIVE) {
                    ImGui::SetItemDefaultFocus();
                }

                if (ImGui::Selectable(
                        "Orthographic",
                        projection_type ==
                            Camera::ProjectionType::ORTHOGRAPHIC)) {
                    camera.set_projection_type(
                        Camera::ProjectionType::ORTHOGRAPHIC);
                }

                if (projection_type == Camera::ProjectionType::ORTHOGRAPHIC) {
                    ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }

            if (camera.projection_type() ==
                Camera::ProjectionType::PERSPECTIVE) {
                float fov_degrees = camera.fov();
                if (ImGui::DragFloat("FOV (degrees)", &fov_degrees)) {
                    camera.set_fov(fov_degrees);
                }

                float z_near = camera.perspective_z_near();
                if (ImGui::DragFloat("Near clip", &z_near)) {
                    camera.set_perspective_z_near(z_near);
                }

                float z_far = camera.perspective_z_far();
                if (ImGui::DragFloat("far clip", &z_far)) {
                    camera.set_perspective_z_far(z_far);
                }
            }

            if (camera.projection_type() ==
                Camera::ProjectionType::ORTHOGRAPHIC) {
                float ortho_size = camera.orthographic_size();
                if (ImGui::DragFloat("Orthographic size", &ortho_size)) {
                    camera.set_orthographic_size(ortho_size);
                }

                float z_near = camera.orthographic_z_near();
                if (ImGui::DragFloat("Near clip", &z_near)) {
                    camera.set_orthographic_z_near(z_near);
                }

                float z_far = camera.orthographic_z_far();
                if (ImGui::DragFloat("far clip", &z_far)) {
                    camera.set_orthographic_z_far(z_far);
                }
            }

            ImGui::TreePop();
        }

        if (ImGui::Button("-")) {
            game_object.remove_component<CameraComponent>();
        }
    }

    if (ImGui::BeginPopupContextItem(ADD_COMPONENT_POPUP_ID)) {

        if (ImGui::Selectable("Camera component")) {
            game_object.add_component<CameraComponent>();
        }

        if (ImGui::Selectable("A component")) {
        }

        if (ImGui::Selectable("B component")) {
        }

        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    if (ImGui::Button("Add component")) {
        ImGui::OpenPopup(ADD_COMPONENT_POPUP_ID);
    }
}

} // namespace SGE
