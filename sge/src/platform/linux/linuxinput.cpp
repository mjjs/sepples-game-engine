#include "engine/core/input.h"
#include "platform/linux/linuxinput.h"

#include "engine/event/event.h"
#include "engine/event/eventdispatcher.h"
#include "engine/event/mousebuttonpressedevent.h"
#include "engine/event/mousebuttonreleasedevent.h"
#include "engine/event/mousemovedevent.h"
#include "engine/event/mousescrolledevent.h"
#include "engine/event/keypressedevent.h"
#include "engine/event/keyreleasedevent.h"

#include <cstdint>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <utility>

namespace SGE {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
Input* Input::instance_ = new LinuxInput();

void LinuxInput::update_impl()
{
    last_keys_ = current_keys_;
    last_mouse_keys_ = current_mouse_keys_;
}

void LinuxInput::handle_input_event_impl(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(LinuxInput::handle_key_down));
    dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FN(LinuxInput::handle_key_up));
    dispatcher.dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(LinuxInput::handle_mouse_button_down));
    dispatcher.dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(LinuxInput::handle_mouse_button_released));
    dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FN(LinuxInput::handle_mouse_motion));
    dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(LinuxInput::handle_mouse_scroll));
}

bool LinuxInput::handle_key_down(KeyPressedEvent& event)
{
    current_keys_.insert(event.key_code());
    return true;
}

bool LinuxInput::handle_key_up(KeyReleasedEvent& event)
{
    last_keys_.insert(event.key_code());
    current_keys_.erase(event.key_code());
    return true;
}

bool LinuxInput::handle_mouse_button_down(MouseButtonPressedEvent& event)
{
    current_mouse_keys_.insert(event.key_code());
    return true;
}

bool LinuxInput::handle_mouse_button_released(MouseButtonReleasedEvent& event)
{
    last_mouse_keys_.insert(event.key_code());
    current_mouse_keys_.erase(event.key_code());
    return true;
}

bool LinuxInput::handle_mouse_motion(MouseMovedEvent& event)
{
    mouse_position_ = event.position();
    return true;
}

// TODO: Implement mouse scrolling
bool LinuxInput::handle_mouse_scroll([[ maybe_unused ]] MouseScrolledEvent& event)
{
    return true;
}

bool LinuxInput::is_key_down_impl(SDL_Keycode key_code)
{
    return current_keys_.find(key_code) != current_keys_.end();
}

bool LinuxInput::is_key_up_impl(SDL_Keycode key_code)
{
    return !is_key_down_impl(key_code);
}

bool LinuxInput::is_key_just_pressed_impl(SDL_Keycode key_code)
{
    return is_key_down_impl(key_code) && last_keys_.find(key_code) == last_keys_.end();
}

bool LinuxInput::is_mouse_button_down_impl(std::uint8_t key_code)
{
    return current_mouse_keys_.find(key_code) != current_mouse_keys_.end();
}

bool LinuxInput::is_mouse_button_up_impl(std::uint8_t key_code)
{
    return !is_mouse_button_down_impl(key_code);
}

bool LinuxInput::is_mouse_button_just_pressed_impl(std::uint8_t key_code)
{
    return is_mouse_button_down_impl(key_code) &&
        last_mouse_keys_.find(key_code) == last_mouse_keys_.end();
}

Vector2 LinuxInput::get_mouse_position_impl()
{
    return mouse_position_;
}

} // namespace SGE
