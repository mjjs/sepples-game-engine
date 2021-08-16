#ifndef _SGE_INPUT_H
#define _SGE_INPUT_H

#include "engine/event/keyboardevent.h"
#include "engine/event/mousebuttonevent.h"
#include "engine/event/mousemovedevent.h"
#include "engine/event/mousescrolledevent.h"

#include <SDL2/SDL_keycode.h>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace SGE
{

class Game;

class Input
{
    friend class Game;

  private:
    static Input*
        instance_; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

    static void handle_input_event(Event& event);
    static void update();

  protected:
    virtual void handle_input_event_impl(Event& event) = 0;
    virtual void update_impl()                         = 0;

    virtual bool is_key_down_impl(SDL_Keycode key_code)         = 0;
    virtual bool is_key_up_impl(SDL_Keycode key_code)           = 0;
    virtual bool is_key_just_pressed_impl(SDL_Keycode key_code) = 0;

    virtual bool is_mouse_button_down_impl(std::uint8_t key_code)         = 0;
    virtual bool is_mouse_button_up_impl(std::uint8_t key_code)           = 0;
    virtual bool is_mouse_button_just_pressed_impl(std::uint8_t key_code) = 0;

    virtual std::pair<float, float> get_mouse_position_impl() = 0;

  public:
    static bool is_key_down(SDL_Keycode key_code);
    static bool is_key_up(SDL_Keycode key_code);
    static bool is_key_just_pressed(SDL_Keycode key_code);
    static bool is_mouse_button_down(std::uint8_t key_code);
    static bool is_mouse_button_up(std::uint8_t key_code);
    static bool is_mouse_button_just_pressed(std::uint8_t key_code);
    static std::pair<float, float> get_mouse_position();
};

} // namespace SGE
#endif
