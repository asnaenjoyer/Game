#ifndef APP_H
#define APP_H

#include <memory>

#include <SDL3/SDL.h>

#include "Image/ImageLoader.h"

class App {
    const char* title;
    int width;
    int height;
    bool running;

    bool init();
    void processEvents();
    void render() const;

protected:
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderer;
    std::shared_ptr<ImageLoader> imageLoader;

    virtual bool initializeResources();
    virtual void update();
    virtual void getButton(SDL_Keycode key);
    virtual void draw() const;

public:
    App(const char* title, int width, int height);
    virtual ~App();

    void run();
    void cleanup();
};

#endif
