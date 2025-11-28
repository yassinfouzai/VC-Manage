#ifndef APPLICATION
#define APPLICATION

#include "utils.hpp"
#include "window.hpp"


class Application {
public:
    Application(const WindowSettings& settings);
    ~Application();
    int run();
    void stop();

private:
    Window window;
    bool running;
    int exitStatus{0};
};



#endif // !APPLICATION
