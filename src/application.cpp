#include "../include/application.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include "../tools/imgui/imgui.h"
#include "../tools/imgui/imgui_impl_sdl2.h"
#include "../tools/imgui/imgui_impl_sdlrenderer2.h"

Application::Application(const WindowSettings &settings) : window(settings) {
  // Init window
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
    exitStatus = 1;
  }
  // ImGUI init
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplSDL2_InitForSDLRenderer(window.getNativeWindow(),
                                    window.getNativeRenderer());
  ImGui_ImplSDLRenderer2_Init(window.getNativeRenderer());
}

void Application::stop() {
    running = false;
}

int Application::run() {
  bool running = true;
  while (running) {
    SDL_Event event{};
    while (SDL_PollEvent(&event) == 1) {
      ImGui_ImplSDL2_ProcessEvent(&event);

      if (event.type == SDL_QUIT) {
        stop();
      }
    }

    // Start ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Demo Window");
    ImGui::Button("Hello!");
    ImGui::End();

    // Rendering
    ImGui::Render();

    SDL_SetRenderDrawColor(window.getNativeRenderer(), 100, 100, 100, 255);
    SDL_RenderClear(window.getNativeRenderer());
    SDL_RenderPresent(window.getNativeRenderer());
  }

  return exitStatus;
}

Application::~Application() {
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  SDL_Quit();
}
