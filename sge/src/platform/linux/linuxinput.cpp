#include "engine/core/input.h"
#include "engine/event/event.h"
#include "engine/event/keypressedevent.h"
#include "engine/event/keyreleasedevent.h"
#include "engine/event/mousebuttonpressedevent.h"
#include "engine/event/mousebuttonreleasedevent.h"
#include "engine/event/mousemovedevent.h"
#include "engine/event/mousescrolledevent.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <cstdint>
#include <unordered_set>
#include <utility>

namespace SGE
{

static bool handle_key_down(KeyPressedEvent& event);
static bool handle_key_up(KeyReleasedEvent& event);
static bool handle_mouse_button_down(MouseButtonPressedEvent& event);
static bool handle_mouse_button_released(MouseButtonReleasedEvent& event);
static bool handle_mouse_motion(MouseMovedEvent& event);
static bool handle_mouse_scroll(MouseScrolledEvent& event);

struct InputState {
    // Keyboard
    std::unordered_set<SDL_Keycode> last_keys_{};
    std::unordered_set<SDL_Keycode> current_keys_{};

    // Mouse
    std::unordered_set<std::uint8_t> last_mouse_keys_{};
    std::unordered_set<std::uint8_t> current_mouse_keys_{};
    std::pair<float, float> mouse_position_{};
} static input_state; // NOLINT

void Input::update()
{
    input_state.last_keys_       = input_state.current_keys_;
    input_state.last_mouse_keys_ = input_state.current_mouse_keys_;
}

void Input::handle_input_event(Event& event)
{
    Event::dispatch<KeyPressedEvent>(event, BIND_EVENT_FN(handle_key_down));
    Event::dispatch<KeyReleasedEvent>(event, BIND_EVENT_FN(handle_key_up));
    Event::dispatch<MouseButtonPressedEvent>(
        event, BIND_EVENT_FN(handle_mouse_button_down));
    Event::dispatch<MouseButtonReleasedEvent>(
        event, BIND_EVENT_FN(handle_mouse_button_released));
    Event::dispatch<MouseMovedEvent>(event, BIND_EVENT_FN(handle_mouse_motion));
    Event::dispatch<MouseScrolledEvent>(event,
                                        BIND_EVENT_FN(handle_mouse_scroll));
}

bool handle_key_down(KeyPressedEvent& event)
{
    input_state.current_keys_.insert(event.key_code());
    return true;
}

bool handle_key_up(KeyReleasedEvent& event)
{
    input_state.last_keys_.insert(event.key_code());
    input_state.current_keys_.erase(event.key_code());
    return true;
}

bool handle_mouse_button_down(MouseButtonPressedEvent& event)
{
    input_state.current_mouse_keys_.insert(event.key_code());
    return true;
}

bool handle_mouse_button_released(MouseButtonReleasedEvent& event)
{
    input_state.last_mouse_keys_.insert(event.key_code());
    input_state.current_mouse_keys_.erase(event.key_code());
    return true;
}

bool handle_mouse_motion(MouseMovedEvent& event)
{
    input_state.mouse_position_ = event.position();
    return true;
}

// TODO: Implement mouse scrolling
bool handle_mouse_scroll([[maybe_unused]] MouseScrolledEvent& event)
{
    return true;
}

bool Input::is_key_down(SDL_Keycode key_code)
{
    return input_state.current_keys_.find(key_code) !=
           input_state.current_keys_.end();
}

bool Input::is_key_up(SDL_Keycode key_code)
{
    return !is_key_down(key_code);
}

bool Input::is_key_just_pressed(SDL_Keycode key_code)
{
    return is_key_down(key_code) && input_state.last_keys_.find(key_code) ==
                                        input_state.last_keys_.end();
}

bool Input::is_mouse_button_down(std::uint8_t key_code)
{
    return input_state.current_mouse_keys_.find(key_code) !=
           input_state.current_mouse_keys_.end();
}

bool Input::is_mouse_button_up(std::uint8_t key_code)
{
    return !is_mouse_button_down(key_code);
}

bool Input::is_mouse_button_just_pressed(std::uint8_t key_code)
{
    return is_mouse_button_down(key_code) &&
           input_state.last_mouse_keys_.find(key_code) ==
               input_state.last_mouse_keys_.end();
}

std::pair<float, float> Input::get_mouse_position()
{
    return input_state.mouse_position_;
}

} // namespace SGE
