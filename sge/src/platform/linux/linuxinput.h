#ifndef _SGE_LINUXINPUT_H
#define _SGE_LINUXINPUT_H

#include "engine/event/event.h"
#include "engine/core/input.h"
#include "engine/event/keypressedevent.h"
#include "engine/event/keyreleasedevent.h"
#include "engine/event/mousebuttonpressedevent.h"
#include "engine/event/mousebuttonreleasedevent.h"
#include "engine/event/mousemovedevent.h"
#include "engine/event/mousescrolledevent.h"
#include "engine/math/vector2.h"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>

namespace SGE
{

class LinuxInput : public Input
{
  private:
    // Keyboard
    std::unordered_set<SDL_Keycode> last_keys_{};
    std::unordered_set<SDL_Keycode> current_keys_{};

    // Mouse
    std::unordered_set<std::uint8_t> last_mouse_keys_{};
    std::unordered_set<std::uint8_t> current_mouse_keys_{};
    Vector2 mouse_position_{};

    bool handle_key_down(KeyPressedEvent& event);
    bool handle_key_up(KeyReleasedEvent& event);
    bool handle_mouse_button_down(MouseButtonPressedEvent& event);
    bool handle_mouse_button_released(MouseButtonReleasedEvent& event);
    bool handle_mouse_motion(MouseMovedEvent& event);
    bool handle_mouse_scroll(MouseScrolledEvent& event);

  protected:
    void handle_input_event_impl(Event& event) override;
    void update_impl() override;
    bool is_key_down_impl(SDL_Keycode key_code) override;
    bool is_key_up_impl(SDL_Keycode key_code) override;
    bool is_key_just_pressed_impl(SDL_Keycode key_code) override;
    bool is_mouse_button_down_impl(std::uint8_t key_code) override;
    bool is_mouse_button_up_impl(std::uint8_t key_code) override;
    bool is_mouse_button_just_pressed_impl(std::uint8_t key_code) override;
    Vector2 get_mouse_position_impl() override;
};

} // namespace SGE

#endif
