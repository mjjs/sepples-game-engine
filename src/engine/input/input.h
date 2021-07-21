#ifndef _SGE_INPUT_H
#define _SGE_INPUT_H

#include "vector2.h"

#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <SDL2/SDL_keycode.h>

namespace SGE {
    class Engine;

    class Input {
        friend class Engine;

    private:
        // Keyboard
        std::unordered_set<SDL_Scancode> last_keys_{};
        std::unordered_set<SDL_Scancode> current_keys_{};

        // Mouse
        std::unordered_set<std::uint32_t> last_mouse_keys_{};
        std::unordered_set<std::uint32_t> current_mouse_keys_{};
        std::pair<float, float> mouse_position_{};

        static Input* instance_; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

        static void poll_events()
        {
            return instance_->poll_events_impl();
        }

    protected:
        virtual bool is_key_down_impl(SDL_Scancode key_code) = 0;
        virtual bool is_key_up_impl(SDL_Scancode key_code) = 0;
        virtual bool is_key_just_pressed_impl(SDL_Scancode key_code) = 0;

        virtual bool is_mouse_button_down_impl(std::uint8_t key_code) = 0;
        virtual bool is_mouse_button_up_impl(std::uint8_t key_code) = 0;
        virtual bool is_mouse_button_just_pressed_impl(std::uint8_t key_code) = 0;

        virtual std::pair<float, float> get_mouse_position_impl() = 0;

        virtual void poll_events_impl() = 0;

    public:
        inline static bool is_key_down(SDL_Scancode key_code)
        {
            return instance_->is_key_down_impl(key_code);
        }

        inline static bool is_key_up(SDL_Scancode key_code)
        {
            return instance_->is_key_up_impl(key_code);
        }

        inline static bool is_key_just_pressed(SDL_Scancode key_code)
        {
            return instance_->is_key_just_pressed_impl(key_code);
        }

        inline static bool is_mouse_button_down(std::uint8_t key_code)
        {
            return instance_->is_mouse_button_down_impl(key_code);
        }

        inline static bool is_mouse_button_up(std::uint8_t key_code)
        {
            return instance_->is_mouse_button_up_impl(key_code);
        }

        inline static bool is_mouse_button_just_pressed(std::uint8_t key_code)
        {
            return instance_->is_mouse_button_just_pressed_impl(key_code);
        }

        inline static std::pair<float, float> get_mouse_position()
        {
            return instance_->get_mouse_position_impl();
        }
    };
} // namespace SGE
#endif
