#ifndef _SGE_WINDOW_H
#define _SGE_WINDOW_H

#include "vector2.h"

#include <cstddef>
#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace SGE {

class Window {
    private:
        SDL_Window* window_;
        SDL_GLContext context_;

        size_t width_;
        size_t height_;

    public:
        Window(size_t width, size_t height, const std::string& title);
        ~Window();

        Window(const Window&) = delete;
        Window(const Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(const Window&&) = delete;

        inline void fill(float r, float g, float b, float a) const
        {
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        inline void clear() const
        {
            fill(0.0, 0.0, 0.0, 1.0);
        }

        inline void flip() const
        {
            SDL_GL_SwapWindow(window_);
        }

        inline Math::Vector2 get_center() const
        {
            return Math::Vector2{
                static_cast<float>(width_)/2,
                static_cast<float>(height_)/2,
            };
        }
};

} // namespace SGE
#endif
