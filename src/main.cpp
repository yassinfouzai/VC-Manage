#include <SDL2/SDL.h>
#include "../tools/imgui/imgui.h"
#include "../tools/imgui/imgui_impl_sdl2.h"
#include "../tools/imgui/imgui_impl_sdlrenderer2.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL + ImGui",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        960, 640, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    bool running = true;
    float x = 50.0f;
    float y = 200.0f;
    float speed = 2.0f;
    float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) running = false;
        }

        // --- Update your rectangle ---
        x += speed;   // move slowly to the right
        if (x > 800) x = -50;   // wrap around

        // --- Start ImGui frame ---
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Control Panel");
        ImGui::Text("Rectangle X: %.1f", x);
        ImGui::Text("Rectangle Y: %.1f", y);
        ImGui::SliderFloat("Speed", &speed, 0.1f, 10.0f);
        ImGui::ColorEdit4("Color", color);
        ImGui::End();

        ImGui::Render();

        // --- SDL Render everything ---
        SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,
            (Uint8)(color[0] * 255),
            (Uint8)(color[1] * 255),
            (Uint8)(color[2] * 255),
            (Uint8)(color[3] * 255));

        SDL_Rect r{(int)x, (int)y, 60, 60};
        SDL_RenderFillRect(renderer, &r);

        // --- Draw ImGui on top ---
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

        SDL_RenderPresent(renderer);
    }

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
