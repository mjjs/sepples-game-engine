#include "input.h"
#include "linuxinput.h"

#include <cstdint>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <utility>

namespace SGE {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
Input* Input::instance_ = new LinuxInput();

void LinuxInput::poll_events_impl()
{
    SDL_PumpEvents();
    poll_keyboard_events();
    poll_mouse_events();
}

void LinuxInput::poll_mouse_events()
{
    last_mouse_keys_ = current_mouse_keys_;
    current_mouse_keys_.clear();

    int x = 0;
    int y = 0;

    std::uint32_t mouse_state = SDL_GetMouseState(&x, &y);

    mouse_position_ = {x, y};

    const std::vector<std::uint8_t> mouse_buttons = {SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT};

    for (const auto& button : mouse_buttons) {
        if ((mouse_state & SDL_BUTTON(button)) != 0U) {
            current_mouse_keys_.insert(button);
        }
    }
}

void LinuxInput::poll_keyboard_events()
{
    last_keys_ = current_keys_;
    current_keys_.clear();

    keyboard_state_ = SDL_GetKeyboardState(&num_keys_);

    for (int i = 0; i < num_keys_; ++i) {
        if (keyboard_state_[i]) {
            current_keys_.insert(static_cast<SDL_Scancode>(i));
        }
    }
}

} // namespace SGE
