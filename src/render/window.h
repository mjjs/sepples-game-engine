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

        void fill(float r, float g, float b, float a) const;
        void clear() const;
        void flip() const;
        Vector2 get_center() const;
};

} // namespace SGE
#endif
