#ifndef _INPUT_H
#define _INPUT_H

#include "vector2.h"

#include <cstdint>
#include <unordered_map>
#include <unordered_set>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

class Input {

private:
    // Keyboard
    std::unordered_set<SDL_Keycode> last_keys;
    std::unordered_set<SDL_Keycode> current_keys;

    // Mouse
    std::unordered_set<std::uint32_t> last_mouse_keys;
    std::unordered_set<std::uint32_t> current_mouse_keys;

    Math::Vector2 mouse_position;

public:
    void key_event(const SDL_Event&);
    void clear_state();
    void update();

    bool is_key_down(SDL_KeyCode) const;
    bool is_key_up(SDL_KeyCode) const;
    bool is_key_just_pressed(SDL_KeyCode key_code) const;

    bool is_mouse_button_down(std::uint32_t) const;
    bool is_mouse_button_up(std::uint32_t) const;
    bool is_mouse_button_just_pressed(std::uint32_t) const;

    Math::Vector2 get_mouse_position() const;
};
#endif
