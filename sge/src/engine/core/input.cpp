#include "engine/core/input.h"

namespace SGE {

void Input::handle_input_event(Event& event)
{
    instance_->handle_input_event_impl(event);
}

void Input::update()
{
    instance_->update_impl();
}

bool Input::is_key_down(SDL_Keycode key_code)
{
    return instance_->is_key_down_impl(key_code);
}

bool Input::is_key_up(SDL_Keycode key_code)
{
    return instance_->is_key_up_impl(key_code);
}

bool Input::is_key_just_pressed(SDL_Keycode key_code)
{
    return instance_->is_key_just_pressed_impl(key_code);
}

bool Input::is_mouse_button_down(std::uint8_t key_code)
{
    return instance_->is_mouse_button_down_impl(key_code);
}

bool Input::is_mouse_button_up(std::uint8_t key_code)
{
    return instance_->is_mouse_button_up_impl(key_code);
}

bool Input::is_mouse_button_just_pressed(std::uint8_t key_code)
{
    return instance_->is_mouse_button_just_pressed_impl(key_code);
}

Vector2 Input::get_mouse_position()
{
    return instance_->get_mouse_position_impl();
}

} // namespace SGE
