#include "../include/application.hpp"
#include "../include/buildings/batiment.hpp"
#include "../include/buildings/commercial.hpp"
#include "../include/buildings/resident.hpp"
#include "../include/buildings/parc.hpp"
#include "../include/cycle/simulation.hpp"
#include "../tools/imgui/imgui.h"
#include "../tools/imgui/imgui_impl_sdl2.h"
#include "../tools/imgui/imgui_impl_sdlrenderer2.h"
#include <cstdlib>
#include <iostream>

Application::Application(const WindowSettings &settings)
    : window(settings), running(true),
      sim("Test Town", Difficulty::Medium) // initialize member objects here
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

void Application::displayInspect(ImGuiWindowFlags flags, float x, float y,
                                 int value, bool isHoveringRect, float speed,
                                 float recwidth) const {
  float controlPanelWidth = window.getWidth() * 0.25f;
  if (controlPanelWidth < 200.0f)
    controlPanelWidth = 200.0f;

  ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(
      viewport->Pos.x + viewport->Size.x - controlPanelWidth, viewport->Pos.y));
  ImGui::SetNextWindowSize(
      ImVec2(controlPanelWidth, viewport->Size.y - taskbarHeight));

  ImGui::Begin("Inspector", nullptr, flags);

  if (isHoveringRect) {
    Batiment *batiment = sim.getVille().getBatimentByPos(static_cast<int>(x),
                                                         static_cast<int>(y));
    if (batiment) {
      batiment->afficheDetails();
      // Size
      ImGui::Text("Size: %.1f x %.1f tiles", batiment->surface.largeur,
                  batiment->surface.longeur);

    } else {
      ImGui::Text("No building at this tile");
    }

    // Also show tile info
    ImGui::Separator();
    ImGui::Text("World Info:");
    ImGui::Separator();
    ImGui::Text("Tile coords: (%.1f, %.1f)", x, y);
    ImGui::Text("Tile value: %d", value);
    ImGui::Text("Rectangle width: %.1f", recwidth);

  } else {
    ImGui::Text("Hover over the rectangle to see info");
  }

  ImGui::End();
}

void Application::displayTaskBar(ImGuiWindowFlags flags, Simulation &sim) {
  ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(
      viewport->Pos.x, viewport->Pos.y + viewport->Size.y - taskbarHeight));
  ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, taskbarHeight));

  ImGui::Begin("Taskbar", nullptr, flags | ImGuiWindowFlags_NoTitleBar);

  ImGui::Text("%s :", sim.getVille().getNom().c_str());
  ImGui::SameLine();
  ImGui::Text("Population: %d", sim.getVille().getPopulation());
  ImGui::SameLine();
  ImGui::Text("Employed: %d / %d", sim.getVille().calculerEmploiActuel(),
              sim.getVille().calculerCapaciteEmploi());
  ImGui::SameLine();
  ImGui::Text("Unemployment: %.1f%%", sim.getVille().calculerTauxChomage());
  ImGui::SameLine();
  ImGui::Text("Satisfaction: %d%%", sim.getVille().getSatisfaction());
  ImGui::SameLine();
  ImGui::Text("Budget: %.2f", sim.getVille().getBudget());
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
}

void Application::displayToolkit(ImGuiWindowFlags flags) {
  float width = window.getWidth() * 0.2;

  ImGuiViewport *viewport = ImGui::GetMainViewport();

  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSize(ImVec2(width, viewport->Size.y - taskbarHeight));

  ImGui::Begin("Toolkit", nullptr, flags);

  ImGui::Button("House");
  ImGui::SameLine();
  ImGui::Button("Appartement");

  ImGui::Button("Cinema");
  ImGui::SameLine();
  ImGui::Button("Bank");

  ImGui::End();
}

void Application::checkEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    ImGui_ImplSDL2_ProcessEvent(&event);

    if (event.type == SDL_QUIT)
      running = false;

    if (event.type == SDL_MOUSEWHEEL) {
      float oldScale = scale;
      if (event.wheel.y > 0)
        scale *= 1.1f;
      if (event.wheel.y < 0)
        scale *= 0.9f;
      if (scale < 1.0f)
        scale = 1.0f;
      if (scale > 20.0f)
        scale = 20.0f;

      int mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);
      float worldX_before = cameraX + mouseX / oldScale;
      float worldY_before = cameraY + mouseY / oldScale;
      float worldX_after = cameraX + mouseX / scale;
      float worldY_after = cameraY + mouseY / scale;

      cameraX += (worldX_before - worldX_after);
      cameraY += (worldY_before - worldY_after);
    }
  }
}

int Application::run() {
  // Initialize Simulation
  sim.getVille().setBudget(1000);
  sim.getVille().calculerPolutionTotale();
  sim.getVille().calculerSatisfactionTotale();
  sim.getVille().ajoutBatiment(Resident::createHouse(&sim.getVille(), 25, 25));
  sim.getVille().ajoutBatiment(Comercial::createCinema(&sim.getVille(), 30, 35));
  sim.getVille().ajoutBatiment(Parc::createPark(&sim.getVille(), 10, 15));

  // Grid constants
  const int ROWS = 64;
  const int COLS = 64;
  const int TILE_SIZE = 32;
  const int TILES_X = 5;
  const int TILES_Y = 5;
  const int TILE_COUNT = TILES_X * TILES_Y;

  // ----------------------------GRID-------------------------

  // Tilemap init
  int tilemap[ROWS][COLS] = {};
  for (int y = 0; y < ROWS; ++y)
    for (int x = 0; x < COLS; ++x)
      tilemap[y][x] = 6 + std::rand() % 4; // random grass tiles as default

  // Place buildings
  for (const auto &buildingPtr : sim.getVille().batiments) {
    const Batiment &building = *buildingPtr;

    int width = 1, height = 1;
    switch (building.type) {
    case TypeBatiment::Cinema:
      width = 2;
      height = 1;
      break;
    case TypeBatiment::Mall:
      width = 3;
      height = 3;
      break;
    case TypeBatiment::Park:
      width = 2;
      height = 2;
      break;
    case TypeBatiment::House:
    case TypeBatiment::Apartment:
    case TypeBatiment::Bank:
    case TypeBatiment::PowerPlant:
    case TypeBatiment::WaterTreatmentPlant:
    case TypeBatiment::UtilityPlant:
      width = 1;
      height = 1;
      break;
    default:
      break;
    }

    for (int dy = 0; dy < height; ++dy) {
      for (int dx = 0; dx < width; ++dx) {
        int x = building.position.x + dx;
        int y = building.position.y + dy;
        if (x >= 0 && x < COLS && y >= 0 && y < ROWS) {
          int tile = 0;
          switch (building.type) {
          case TypeBatiment::Cinema:
            tile = 10 + dx;
            break;
          case TypeBatiment::Park:
            tile = 15 + dy * 5 + dx;
            break;
          case TypeBatiment::Mall:
            tile = 12 + dy * 5 + dx;
            break;
          case TypeBatiment::House:
            tile = 0; // house tile index in tileset
            break;
          case TypeBatiment::Apartment:
            tile = 1;
            break;
          case TypeBatiment::Bank:
            tile = 2;
            break;
          case TypeBatiment::PowerPlant:
            tile = 3;
            break;
          case TypeBatiment::WaterTreatmentPlant:
            tile = 4;
            break;
          case TypeBatiment::UtilityPlant:
            tile = 5;
            break;
          default:
            tile = 6; // fallback to grass
            break;
          }
          tilemap[y][x] = std::min(tile, TILE_COUNT - 1);
        }
      }
    }
  }

  // Tileset source rectangles
  SDL_Rect src[TILE_COUNT];
  int idx = 0;
  for (int ty = 0; ty < TILES_Y; ++ty) {
    for (int tx = 0; tx < TILES_X; ++tx) {
      src[idx++] = {tx * TILE_SIZE, ty * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    }
  }
  // -----------------------------------------------------
  SDL_Renderer *renderer = window.getNativeRenderer();

  scale = 2.0f;
  cameraX = 0.0f;
  cameraY = 0.0f;
  speed = 5.0f;
  taskbarHeight = 40.0f;
  running = true;

  const Uint8 *keystate = SDL_GetKeyboardState(nullptr);

  while (running) {
    checkEvent();

    float moveSpeed = speed / scale;
    if (keystate[SDL_SCANCODE_W])
      cameraY -= moveSpeed;
    if (keystate[SDL_SCANCODE_S])
      cameraY += moveSpeed;
    if (keystate[SDL_SCANCODE_A])
      cameraX -= moveSpeed;
    if (keystate[SDL_SCANCODE_D])
      cameraX += moveSpeed;

    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui::NewFrame();

    ImGuiIO &io = ImGui::GetIO();
    bool imguiBlockingMouse = io.WantCaptureMouse;

    bool insideMap = false;
    int tileX = -1, tileY = -1;
    int hoveredTile = -1;
    bool hoveredValid = false;

    if (!imguiBlockingMouse) {
      ImVec2 mousePos = ImGui::GetMousePos();
      float worldX = cameraX + mousePos.x / scale;
      float worldY = cameraY + mousePos.y / scale;

      tileX = int(worldX) / TILE_SIZE;
      tileY = int(worldY) / TILE_SIZE;

      insideMap = tileX >= 0 && tileX < COLS && tileY >= 0 && tileY < ROWS;

      if (insideMap) {
        hoveredTile = tilemap[tileY][tileX];
        hoveredValid = hoveredTile >= 0;
      }
    }

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;

    // Display UI
    displayToolkit(flags);
    displayInspect(flags, tileX, tileY, hoveredTile, hoveredValid, speed,
                   TILE_SIZE);
    displayTaskBar(flags, sim);

    ImGui::Render();

    SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
    SDL_RenderClear(renderer);

    // Render tiles
    for (int y = 0; y < ROWS; ++y) {
      for (int x = 0; x < COLS; ++x) {
        int tile = tilemap[y][x];
        SDL_Rect dest = {int((x * TILE_SIZE - cameraX) * scale),
                         int((y * TILE_SIZE - cameraY) * scale),
                         int(TILE_SIZE * scale), int(TILE_SIZE * scale)};
        SDL_RenderCopy(renderer, window.getTexture(), &src[tile], &dest);
      }
    }

    // Hover outline
    if (insideMap) {
      SDL_Rect outline = {int((tileX * TILE_SIZE - cameraX) * scale),
                          int((tileY * TILE_SIZE - cameraY) * scale),
                          int(TILE_SIZE * scale), int(TILE_SIZE * scale)};
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderDrawRect(renderer, &outline);
    }

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(16);
    sim.tick(0.016f);
  }

  return exitStatus;
}
