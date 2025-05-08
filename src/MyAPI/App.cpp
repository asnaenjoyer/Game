#include "App.h"
#include <iostream>

App::App(const char* title, int width, int height)
    : title(title), width(width), height(height), running(false) {}

App::~App() {
    SDL_Quit();
    cleanup();
}

bool App::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != true) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Window* rawWindow = SDL_CreateWindow(title, width, height, 0);
    if (!rawWindow) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }
    window = std::shared_ptr<SDL_Window>(rawWindow, SDL_DestroyWindow);

    SDL_Renderer* rawRenderer = SDL_CreateRenderer(rawWindow, nullptr);
    if (!rawRenderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }
    renderer = std::shared_ptr<SDL_Renderer>(rawRenderer, SDL_DestroyRenderer);

    imageLoader = std::make_shared<ImageLoader>(renderer);

    if (!initializeResources()) {
        std::cerr << "Failed to initialize resources" << std::endl;
        return false;
    }

    return true;
}

void App::run() {
    if (!init()) return;

    running = true;
    while (running) {
        processEvents();
        update();
        render();
    }
}

void App::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
        if (event.type == SDL_EVENT_KEY_DOWN) {
            getButton(event.key.key);
        }
    }
}

bool App::initializeResources() {
    return true;
}

void App::update() {

}

void App::getButton(SDL_Keycode key) {

}

void App::draw() const {

}

void App::render() const {
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.get());

    draw();

    SDL_RenderPresent(renderer.get());
}

void App::cleanup() {
    renderer.reset();
    window.reset();
    SDL_Quit();
}
