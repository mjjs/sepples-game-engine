#include "game/game.h"
#include "input/input.h"
#include "matrix4.h"
#include "window.h"

#define GL3_PROTOTYPES = 1;
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

// GLOBALS -- MOVE TO OWN ENGINE CLASS
std::unique_ptr<Window> window;
std::unique_ptr<Input> input;

// Move these to engine class as well
void render();
void main_loop();
void update(double delta);

void start()
{
    main_loop();
}

void handle_input()
{
    if (input->is_key_down(SDLK_UP)) {
        std::cout << "Up button held down\n";
    }

    if (input->is_key_just_pressed(SDLK_1)) {
        std::cout << "Number 1 just pressed\n";
    }

    if (input->is_mouse_button_just_pressed(SDL_BUTTON_LEFT)) {
        std::cout << "Mouse click at: " << input->get_mouse_position() << '\n';
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

void main_loop()
{
    bool exit = false;

    // TODO: Fix this to a fixed update time step, variable rendering
    // see: http://gameprogrammingpatterns.com/game-loop.html#play-catch-up
    std::uint32_t previous_time = SDL_GetTicks();

    SDL_Event event;

    while (exit == false) {
        std::uint32_t current_time = SDL_GetTicks();
        std::uint32_t elapsed = SDL_TICKS_PASSED(previous_time, current_time);
        double delta = static_cast<double>(elapsed);

        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                exit = true;
                break;
            }

            if (is_input_event(event)) {
                input->key_event(event);
            }
        }

        handle_input();
        input->update();

        render();

        // input->clear_state();
    }
}

void render()
{
    window->fill(1.0, 0.0, 0.0, 1.0);
}

int main()
{
    const std::size_t width = 550;
    const std::size_t height = 550;
    const std::string title = "Game engine!";

    try {
        input = std::make_unique<Input>();
        window = std::make_unique<Window>(width, height, title);

        start();
    } catch (const std::runtime_error& e) {
        std::cout << "Game could not be run: " << e.what() << '\n';
    }

    return 0;
}
