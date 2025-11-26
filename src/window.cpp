#include "../include/window.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

Window::Window(const WindowSettings &settings){

    // c_str() because its a pointer
    // HIGHDPI for 4k Display
    // RESIZABLE for resizing windows

    window = SDL_CreateWindow(settings.title.c_str(), 
                              SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                              settings.width,settings.height,
                              SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "ERROR: Failed to initialize the Renderer" << std::endl;
        return;
    }
}

Window::~Window() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

SDL_Window* Window::getNativeWindow() const {
    return window;
}

SDL_Renderer* Window::getNativeRenderer() const {
    return renderer;
}
