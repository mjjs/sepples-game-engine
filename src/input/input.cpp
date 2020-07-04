#include "input.h"
#include <SDL2/SDL_events.h>
#include <cstddef>
#include <iostream>

void Input::update()
{
    last_keys = current_keys;
    last_mouse_keys = current_mouse_keys;
}

void Input::key_event(const SDL_Event& event)
{
    const SDL_Keycode key_code = event.key.keysym.sym;
    const std::uint32_t mouse_button_code = event.button.button;

    switch (event.type) {
    case SDL_KEYDOWN:
        current_keys.insert(key_code);
        break;
    case SDL_KEYUP:
        last_keys.insert(key_code);
        current_keys.erase(key_code);
        break;
    case SDL_MOUSEBUTTONDOWN:
        current_mouse_keys.insert(mouse_button_code);
        break;
    case SDL_MOUSEBUTTONUP:
        last_mouse_keys.insert(mouse_button_code);
        current_mouse_keys.erase(mouse_button_code);
        break;
    case SDL_MOUSEMOTION:
        mouse_position = Math::Vector2(
                static_cast<float>(event.motion.x),
                static_cast<float>(event.motion.y)
                );
        break;
    }
}

bool Input::is_key_down(SDL_KeyCode key_code) const
{
    return current_keys.find(key_code) != current_keys.end();
}

bool Input::is_key_up(const SDL_KeyCode key_code) const
{
    return !is_key_down(key_code);
}

bool Input::is_key_just_pressed(const SDL_KeyCode key_code) const
{
    return is_key_down(key_code) && last_keys.find(key_code) == last_keys.end();
}

bool Input::is_mouse_button_down(const std::uint32_t mouse_button_code) const
{
    return current_mouse_keys.find(mouse_button_code) != current_mouse_keys.end();
}

bool Input::is_mouse_button_up(const std::uint32_t mouse_button_code) const
{
    return !is_mouse_button_down(mouse_button_code);
}

bool Input::is_mouse_button_just_pressed(const std::uint32_t mouse_button_code) const
{
    return is_mouse_button_down(mouse_button_code) &&
        last_mouse_keys.find(mouse_button_code) == last_mouse_keys.end();
}

Math::Vector2 Input::get_mouse_position() const
{
    return mouse_position;
}
