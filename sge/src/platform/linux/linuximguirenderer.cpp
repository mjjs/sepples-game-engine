#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include "platform/linux/linuximguirenderer.h"

#include "engine/core/game.h"
#include "engine/core/log.h"

#include <SDL.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imguizmo/ImGuizmo.h>
#include <utility>

namespace SGE
{

LinuxImguiRenderer::LinuxImguiRenderer(SDL_Window* window, void* context)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0) {
        style.WindowRounding              = 0.0F;
        style.Colors[ImGuiCol_WindowBg].w = 1.0F;
    }

    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 460");
}

LinuxImguiRenderer::~LinuxImguiRenderer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void LinuxImguiRenderer::start_rendering() const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
}

void LinuxImguiRenderer::end_rendering() const
{
    ImGuiIO& io = ImGui::GetIO();

    const auto& window = Game::get().window();

    io.DisplaySize = ImVec2{static_cast<float>(window.width()),
                            static_cast<float>(window.height())};

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0) {
        SDL_Window* sdl_window    = SDL_GL_GetCurrentWindow();
        SDL_GLContext sdl_context = SDL_GL_GetCurrentContext();

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        SDL_GL_MakeCurrent(sdl_window, sdl_context);
    }
}

bool LinuxImguiRenderer::handle_event(SDL_Event& event) const
{
    if (block_events_) {
        //        ImGuiIO& io  = ImGui::GetIO();
        //        bool handled = (static_cast<int>(io.WantCaptureMouse) |
        //                        static_cast<int>(io.WantCaptureKeyboard)) !=
        //                        0;

        ImGui_ImplSDL2_ProcessEvent(&event);
        return true;
    }

    return false;
}

} // namespace SGE
