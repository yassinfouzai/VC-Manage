#include "../tools/imgui/imgui.h"
#include "../tools/imgui/imgui_impl_sdl2.h"
#include "../tools/imgui/imgui_impl_sdlrenderer2.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

void init(const std::string &windowName, SDL_Window **window,
          SDL_Renderer **renderer) {

  // Init window
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
    exit(1);
  }

  *window =
      SDL_CreateWindow("SDL + ImGui", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 960, 640, SDL_WINDOW_SHOWN);

  // Init Renderer
  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

  // ImGUI init
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplSDL2_InitForSDLRenderer(*window, *renderer);
  ImGui_ImplSDLRenderer2_Init(*renderer);
}

void destroyIMGUI() {
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

void destroyWindow(SDL_Window **window, SDL_Renderer **renderer) {
  SDL_DestroyRenderer(*renderer);
  SDL_DestroyWindow(*window);
  SDL_Quit();
}

int main() {
  SDL_Window *window;
  SDL_Renderer *renderer;

  // initialize the window, the renderer and ImGUI
  init("VC", &window, &renderer);

  bool running = true;
  float x = 50.0f;
  float y = 200.0f;
  float speed = 2.0f;
  float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        running = false;
    }

    // Update your rectangle
    x += speed;
    if (x > 800)
      x = -50;

    // Start ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Control Panel", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
    if (ImGui::Button("Click Me")) {
      std::cout << "Button clicked!" << std::endl;
    }
    ImGui::Text("Rectangle X: %.1f", x);
    ImGui::Text("Rectangle Y: %.1f", y);
    ImGui::SliderFloat("Speed", &speed, 0.1f, 10.0f);
    ImGui::ColorEdit4("Color", color);
    ImGui::End();

    ImGuiViewport *viewport = ImGui::GetMainViewport();

    // Taskbar height
    float taskbarHeight = 40.0f;

    // Set window position and size
    ImGui::SetNextWindowPos(ImVec2(
        viewport->Pos.x, viewport->Pos.y + viewport->Size.y - taskbarHeight));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, taskbarHeight));

    // Window flags for taskbar behavior
    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoFocusOnAppearing;

    // Begin the taskbar window
    if (ImGui::Begin("Taskbar", nullptr, flags)) {
      // Example content: some buttons
      ImGui::Text("Taskbar:");
      ImGui::SameLine();
      if (ImGui::Button("Button 1")) {
        // Action for button
      }
      ImGui::SameLine();
      if (ImGui::Button("Button 2")) {
        // Action for button
      }
    }
    ImGui::End();

    ImGui::Render();

    // SDL Render everything
    SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, (Uint8)(color[0] * 255),
                           (Uint8)(color[1] * 255), (Uint8)(color[2] * 255),
                           (Uint8)(color[3] * 255));

    SDL_Rect r{(int)x, (int)y, 60, 60};
    SDL_RenderFillRect(renderer, &r);

    // Draw ImGUI on top
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

    SDL_RenderPresent(renderer);
  }

  // Destroy the Window, the renderer and the ImGUI
  destroyIMGUI();
  destroyWindow(&window, &renderer);

  return 0;
}
