#ifndef APPLICATION
#define APPLICATION

#include "utils.h"
#include "utils.hpp"
#include "window.hpp"
#include "../tools/imgui/imgui.h"
#include "../tools/imgui/imgui_impl_sdl2.h"
#include "../tools/imgui/imgui_impl_sdlrenderer2.h"

class Application {
public:
    Application(const WindowSettings& settings);
    ~Application();
    void run();

private:
    Window window;
};



#endif // !APPLICATION
