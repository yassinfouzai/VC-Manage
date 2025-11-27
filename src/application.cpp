#include "../include/application.hpp"

Application::Application(const WindowSettings &settings) : window(settings) {
  // ImGUI init
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplSDL2_InitForSDLRenderer(window.getNativeWindow(), window.getNativeRenderer());
  ImGui_ImplSDLRenderer2_Init(window.getNativeRenderer());
}

Application::~Application() {
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}
