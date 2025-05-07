#include "App.h"

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


Game::Game(const char *title, int width, int height) : App(title, width, height){

}

bool Game::initializeResources() {
    texture = std::shared_ptr<SDL_Texture>(
        imageLoader->loadTexture("assets/tileset.png"),
        SDL_DestroyTexture);

    int p = 0;
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            frames[p++] = SDL_FRect{
                static_cast<float>(x * 100),
                static_cast<float>(y * 100),
                100.0f,
                100.0f
            };
        }
    }

    return true;
}

void Game::update() {

}

void Game::getButton(SDL_Keycode key) {
    auto& g = grid.get();
    int x = -1, y = -1;
    for (int i = 0; i < g.size(); ++i)
        for (int j = 0; j < g[i].size(); ++j)
            if (g[i][j] == 0) {
                x = i;
                y = j;
                break;
            }

    switch (key) {
        case SDLK_UP:
            if (x > 0) std::swap(g[x][y], g[x - 1][y]);
            break;
        case SDLK_DOWN:
            if (x < g.size() - 1) std::swap(g[x][y], g[x + 1][y]);
            break;
        case SDLK_LEFT:
            if (y > 0) std::swap(g[x][y], g[x][y - 1]);
            break;
        case SDLK_RIGHT:
            if (y < g.size() - 1) std::swap(g[x][y], g[x][y + 1]);
            break;
        default:
            break;
    }
}

void Game::draw() const {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            int index = i * 4 + j;            // 0..15
            SDL_FRect dstRect = {
                static_cast<float>(j * 100),  // x
                static_cast<float>(i * 100),  // y
                100.0f,
                100.0f
            };
            Cell cell(texture.get(), frames[grid.get(i,j)], dstRect);
            cell.draw(renderer.get());
        }
    }
}

Game::~Game() {
    App::~App();
}
