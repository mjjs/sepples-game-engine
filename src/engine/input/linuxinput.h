#ifndef _SGE_LINUXINPUT_H
#define _SGE_LINUXINPUT_H

#include "input.h"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>

namespace SGE {
    class LinuxInput : public Input {
    private:
        const Uint8* keyboard_state_ = nullptr;
        int num_keys_ = 0;

        // Keyboard
        std::unordered_set<SDL_Scancode> last_keys_{};
        std::unordered_set<SDL_Scancode> current_keys_{};

        // Mouse
        std::unordered_set<std::uint8_t> last_mouse_keys_{};
        std::unordered_set<std::uint8_t> current_mouse_keys_{};
        std::pair<float, float> mouse_position_{};

        void poll_keyboard_events();
        void poll_mouse_events();

    protected:
        inline bool is_key_down_impl(SDL_Scancode key_code) override
        {
            return current_keys_.find(key_code) != current_keys_.end();
        }

        inline bool is_key_up_impl(SDL_Scancode key_code) override
        {
            return !is_key_down_impl(key_code);
        }

        inline bool is_key_just_pressed_impl(SDL_Scancode key_code) override
        {
            return is_key_down_impl(key_code) && last_keys_.find(key_code) == last_keys_.end();
        }

        inline bool is_mouse_button_down_impl(std::uint8_t key_code) override
        {
            return current_mouse_keys_.find(key_code) != current_mouse_keys_.end();
        }

        inline bool is_mouse_button_up_impl(std::uint8_t key_code) override
        {
            return !is_mouse_button_down_impl(key_code);
        }

        inline bool is_mouse_button_just_pressed_impl(std::uint8_t key_code) override
        {
            return is_mouse_button_down_impl(key_code) &&
                last_mouse_keys_.find(key_code) == last_mouse_keys_.end();
        }


        inline std::pair<float, float> get_mouse_position_impl() override
        {
            return mouse_position_;
        }

        void poll_events_impl() override;
    };
} // namespace SGE

#endif
