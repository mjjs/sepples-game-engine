#include "editor.h"

#include "camerascript.h"

#include <imgui.h>
#include <memory>

namespace SGE
{

Editor::Editor()
{
    auto fb_config   = FramebufferConfig{};
    fb_config.width  = 1280;
    fb_config.height = 720;

    framebuffer_ = Framebuffer::create(fb_config);

    active_scene_ = std::make_shared<Scene>();

    auto backpack = active_scene_->add_game_object("backpack");
    auto floor    = active_scene_->add_game_object("floor");
    auto camera   = active_scene_->add_game_object("camera");

    camera.add_component<CameraComponent>();
    camera.add_component<CPPScriptComponent>().bind<CameraScript>();

    backpack.add_component<ModelRendererComponent>(
        std::make_shared<Model>("res/models/backpack.obj"));

    std::vector<Vertex> floor_vertices{
        {{-10, -2, -10}, {0, 1, 0}, {0, 0}},
        {{-10, -2, 30}, {0, 1, 0}, {0, 1}},
        {{30, -2, -10}, {0, 1, 0}, {1, 0}},
        {{30, -2, 30}, {0, 1, 0}, {1, 1}},
    };

    std::vector<std::uint32_t> floor_indices = {0, 1, 2, 2, 1, 3};

    auto red_texture = Texture2D::create(glm::vec4{.8, .2, .3, 1}, 1, 1);

    auto floor_mesh = std::make_shared<Mesh>(
        floor_vertices, floor_indices, Material{red_texture, nullptr, nullptr});

    floor.add_component<MeshRendererComponent>(floor_mesh);

    scene_hierarchy_panel_ = SceneHierarchyPanel{active_scene_};
}

void Editor::update(const float delta)
{
    framebuffer_->bind();
    Renderer::clear_screen();
    active_scene_->update(delta);
    framebuffer_->unbind();
}

void Editor::render_imgui()
{
    static bool opt_fullscreen_persistant     = true;
    bool opt_fullscreen                       = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    if (opt_fullscreen) {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0F);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0F);
        window_flags |= ImGuiWindowFlags_NoTitleBar |
                        ImGuiWindowFlags_NoCollapse |
                        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                        ImGuiWindowFlags_NoBringToFrontOnFocus |
                        ImGuiWindowFlags_NoNavFocus;
    }

    if ((dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0) {
        window_flags |= ImGuiWindowFlags_NoBackground;
    }

    static bool dockspace_open = true;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0F, 0.0F));
    ImGui::Begin("Editor dockspace", &dockspace_open, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen) {
        ImGui::PopStyleVar(2);
    }

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if ((io.ConfigFlags & ImGuiConfigFlags_DockingEnable) != 0) {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0F, 0.0F), dockspace_flags);
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});

    scene_hierarchy_panel_.render_imgui();

    ImGui::Begin("Scene");
    get().window().set_block_imgui_events(!ImGui::IsWindowFocused() ||
                                          !ImGui::IsWindowHovered());

    auto [width, height] = ImGui::GetContentRegionAvail();

    if (width != scene_viewport_width_ || height != scene_viewport_height_) {
        scene_viewport_height_ = height;
        scene_viewport_width_  = width;

        framebuffer_->resize(width, height);
        active_scene_->on_window_resized(width, height);
    }

    std::uint32_t texture_id = framebuffer_->colour_attachment_buffer_id();
    ImGui::Image((void*)texture_id, ImVec2{width, height}, ImVec2{0, 1},
                 ImVec2{1, 0});

    ImGui::End();

    ImGui::PopStyleVar();

    ImGui::End();
}

void Editor::on_viewport_resize(const std::size_t width,
                                const std::size_t height)
{
    active_scene_->on_window_resized(width, height);
}

std::unique_ptr<Game> create_game([[maybe_unused]] int argc,
                                  [[maybe_unused]] char** argv)
{
    return std::make_unique<Editor>();
}

} // namespace SGE
