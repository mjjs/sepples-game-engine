// Is this necessary?
#define GL3_PROTOTYPES = 1;

#include "engine.h"
#include "input.h"
#include "mesh.h"
#include "resourceloader.h"
#include "shader.h"
#include "vector3.h"
#include "window.h"

#include <SDL2/SDL.h>

bool is_input_event(const SDL_Event& event);

Engine::Engine() :
    window{window_width, window_height, window_title}
{}

void Engine::init()
{
}

void Engine::cleanup()
{
    window.cleanup();
}

void Engine::main_loop()
{
    // TODO: Load shaders and meshes from asset files
    const std::vector<Math::Vector3> triangle_vertices{
        {-1.0, -1.0, 0.0},
            {0.0, 1.0, 0.0},
            {1.0, -1.0, 0.0}
    };

    Mesh triangle{triangle_vertices};
    Shader shader{};
    shader.add_vertex_shader(load_shader("basic_vertex.gsls"));
    shader.add_fragment_shader(load_shader("basic_fragment.gsls"));
    shader.compile_shader();

    // TODO: Fix this to a fixed update time step, variable rendering
    // see: http://gameprogrammingpatterns.com/game-loop.html#play-catch-up
    std::uint32_t previous_time = SDL_GetTicks();

    SDL_Event event;

    while (exit_requested == false) {
        std::uint32_t current_time = SDL_GetTicks();
        std::uint32_t elapsed = SDL_TICKS_PASSED(previous_time, current_time);
        double delta = static_cast<double>(elapsed);

        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                exit_requested = true;
                break;
            }

            if (is_input_event(event)) {
                input.key_event(event);
            }
        }

        // Handle game input before input.update();
        input.update();

        // TODO: Move to a render method
        window.fill(1.0, 0.0, 1.0, 1.0);
        shader.bind();
        triangle.draw();
        window.flip();
    }
}

bool is_input_event(const SDL_Event& event)
{
    switch (event.type) {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEMOTION:
        return true;
    }

    return false;
}
