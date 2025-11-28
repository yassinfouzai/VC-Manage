#include "../include/application.hpp"
#include <iostream>
#include "../tools/imgui/imgui.h"
#include "../tools/imgui/imgui_impl_sdl2.h"
#include "../tools/imgui/imgui_impl_sdlrenderer2.h"

Application::Application(const WindowSettings &settings)
    : window(settings), running(true) // initialize member objects here
{
    // Initialize SDL (already done before creating Window would be better in main)
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
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)w, (float)h);

    ImGui_ImplSDL2_InitForSDLRenderer(window.getNativeWindow(), window.getNativeRenderer());
    ImGui_ImplSDLRenderer2_Init(window.getNativeRenderer());
}

Application::~Application() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
}

void Application::stop() {
    running = false;
}

int Application::run() {
    float x = 50.0f, y = 200.0f, speed = 2.0f;
    float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    SDL_Renderer* renderer = window.getNativeRenderer();

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                stop();
        }

        // Update rectangle position
        x += speed;
        if (x > 800) x = -50;

        // Start ImGui frame
        ImGui_ImplSDL2_NewFrame();
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui::NewFrame();

        // Control Panel
        ImGui::Begin("Control Panel", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
        ImGui::Text("Rectangle X: %.1f", x);
        ImGui::Text("Rectangle Y: %.1f", y);
        ImGui::SliderFloat("Speed", &speed, 0.1f, 10.0f);
        ImGui::ColorEdit4("Color", color);
        ImGui::End();

        // Taskbar
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        float taskbarHeight = 40.0f;
        ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + viewport->Size.y - taskbarHeight));
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, taskbarHeight));

        ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing;

        ImGui::Begin("Taskbar", nullptr, flags);
        ImGui::Text("Taskbar:");
        ImGui::SameLine();
        if (ImGui::Button("Button 1")) {}
        ImGui::SameLine();
        if (ImGui::Button("Button 2")) {}
        ImGui::End();

        ImGui::Render();

        // SDL Rendering
        SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,
                               (Uint8)(color[0]*255),
                               (Uint8)(color[1]*255),
                               (Uint8)(color[2]*255),
                               (Uint8)(color[3]*255));

        SDL_Rect r{ (int)x, (int)y, 60, 60 };
        SDL_RenderFillRect(renderer, &r);

        // Render ImGui on top
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), window.getNativeRenderer());

        SDL_RenderPresent(renderer);
    }

    return exitStatus;
}

