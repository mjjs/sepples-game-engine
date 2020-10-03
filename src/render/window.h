#ifndef _SGE_WINDOW_H
#define _SGE_WINDOW_H

#include <cstddef>
#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>

class Window {
private:
    SDL_Window* window;
    SDL_GLContext context;

public:
    Window(size_t width, size_t height, const std::string& title);
    ~Window();

    Window(const Window&) = delete;
    Window(const Window&&) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(const Window&&) = delete;

    void clear();
    void fill(float r, float g, float b, float a) const;
    void flip();
};
#endif
