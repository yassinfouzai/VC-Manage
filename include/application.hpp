#ifndef APPLICATION
#define APPLICATION

#include "utils.hpp"
#include "window.hpp"


class Application {
public:
    explicit Application(const WindowSettings& settings);
    ~Application();
    int run();
    void stop();

    Window getWindow() const;

private:
    Window window;
    bool running;
    int exitStatus{0};
};



#endif // !APPLICATION
