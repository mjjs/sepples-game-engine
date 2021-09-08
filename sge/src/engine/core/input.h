#ifndef _SGE_INPUT_H
#define _SGE_INPUT_H

#include "engine/event/event.h"

#include <SDL2/SDL_keycode.h>
#include <cstdint>
#include <utility>

namespace SGE
{

class Input
{
    friend class Game;

  private:
    static void handle_input_event(Event& event);
    static void update();

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
