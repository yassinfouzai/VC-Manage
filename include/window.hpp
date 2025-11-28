#ifndef WINDOW
#define WINDOW

#include "utils.hpp"
#include <SDL2/SDL.h>

class Window {
public:
    explicit Window(const WindowSettings& settings);
    ~Window();

    SDL_Window* getNativeWindow() const;
    SDL_Renderer* getNativeRenderer() const;
private:
    SDL_Window* window{nullptr};
    SDL_Renderer* renderer{nullptr};
};

#endif // !WINDOW
