#include "../include/application.hpp"
#include "../include/cycle/simulation.hpp"
#include "../tools/imgui/imgui.h"
#include "../tools/imgui/imgui_impl_sdl2.h"
#include "../tools/imgui/imgui_impl_sdlrenderer2.h"
#include <iostream>

Application::Application(const WindowSettings &settings)
    : window(settings), running(true) // initialize member objects here
{
  // Initialize SDL (already done before creating Window would be better in
  // main)
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
    exitStatus = 1;
    running = false;
    return;
  }

  if (!window.getNativeWindow() || !window.getNativeRenderer()) {
    std::cerr << "Failed to create SDL window or renderer\n";
    exitStatus = 1;
    running = false;
    return;
  }

  // ImGui init
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  // Explicitly set DisplaySize to avoid invalid DisplaySize crash
  int w, h;
  SDL_GetWindowSize(window.getNativeWindow(), &w, &h);
  ImGuiIO &io = ImGui::GetIO();
  io.DisplaySize = ImVec2((float)w, (float)h);

  ImGui_ImplSDL2_InitForSDLRenderer(window.getNativeWindow(),
                                    window.getNativeRenderer());
  ImGui_ImplSDLRenderer2_Init(window.getNativeRenderer());
}

Application::~Application() {
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  SDL_Quit();
}

void Application::stop() { running = false; }

int Application::run() {
  float x = 50.0f, y = 200.0f, speed = 2.0f;
  float recwidth = 60.0f;
  float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

  SDL_Renderer *renderer = window.getNativeRenderer();

  Simulation sim("Test Town", Difficulty::Medium);

  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        stop();
    }

    // Update rectangle position
    x += speed;
    if (x > 800)
      x = -50;

    // Start ImGui frame
    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui::NewFrame();
    ImGuiViewport *viewport = ImGui::GetMainViewport();
    float taskbarHeight = 40.0f;
    float controlPanelWidth = window.getWidth() * 0.25;
    if (controlPanelWidth < 200.0f) {
      controlPanelWidth = 200.0f;
    }
    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;

    // Control Panel
    ImGui::SetNextWindowPos(
        ImVec2(viewport->Pos.x + viewport->Size.x - controlPanelWidth,
               viewport->Pos.y));
    ImGui::SetNextWindowSize(
        ImVec2(controlPanelWidth, viewport->Size.y - taskbarHeight));

    ImVec2 mousePos = ImGui::GetMousePos();
    bool isHoveringRect = !ImGui::GetIO().WantCaptureMouse && mousePos.x >= x &&
                          mousePos.x <= x + recwidth && mousePos.y >= y &&
                          mousePos.y <= y + recwidth;

    ImGui::Begin("Inspector", nullptr, flags);
    if (isHoveringRect) {
      ImGui::Text("Rectangle Info:");
      ImGui::Text("Position: (%.1f, %.1f)", x, y);
      ImGui::Text("Size: %.1f", recwidth);
      ImGui::Text("Speed: %.1f", speed);
      ImGui::ColorEdit4("Color", color);
    } else {
      ImGui::Text("Hover over the rectangle to see info");
    }
    ImGui::End();

    // Taskbar
    ImGui::SetNextWindowPos(ImVec2(
        viewport->Pos.x, viewport->Pos.y + viewport->Size.y - taskbarHeight));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, taskbarHeight));

    ImGui::Begin("Taskbar", nullptr, flags | ImGuiWindowFlags_NoTitleBar);
    ImGui::Text("%s :", sim.getVille().getNom().c_str());
    ImGui::SameLine();
    ImGui::Text("Population: 0");
    ImGui::SameLine();
    ImGui::Text("Satisfaction: 0");
    ImGui::SameLine();
    ImGui::Text("Budget: 0");
    ImGui::SameLine();
    ImGui::Text("Cycle Actuel: %d", sim.getCycle());
    ImGui::SameLine();
    ImGui::Text("Cycle : %.1f / %.1f", sim.getCurrentTime(),
                sim.getTimePerCycle());
    ImGui::SameLine();
    if (ImGui::Button("Skip Month")) {
      sim.terminerCycleEarly();
    }
    ImGui::End();

    ImGui::Render();

    // SDL Rendering
    SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, (Uint8)(color[0] * 255),
                           (Uint8)(color[1] * 255), (Uint8)(color[2] * 255),
                           (Uint8)(color[3] * 255));

    SDL_Rect r{(int)x, (int)y, (int)recwidth, (int)recwidth};
    SDL_RenderFillRect(renderer, &r);

    // Render ImGui on top
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(),
                                          window.getNativeRenderer());

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
    sim.tick(0.016); // 1/60
  }

  return exitStatus;
}
