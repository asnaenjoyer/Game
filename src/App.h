#ifndef APP_H
#define APP_H

#include <memory>
#include <array>
#include <iostream>

#include <SDL3/SDL.h>

#include "Image/ImageLoader.h"
#include "Objects/Grid.h"

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

class Game final : public App {
    std::shared_ptr<SDL_Texture> texture;
    std::array<SDL_FRect, 16> frames;
    std::array<std::array<Cell, 4>, 4> cells;
    Grid grid;

    bool initializeResources() override;
    void update() override;
    void getButton(SDL_Keycode key) override;
    void draw() const override;
public:
    Game(const char* title, int width, int height);
    ~Game() override;
};

#endif
