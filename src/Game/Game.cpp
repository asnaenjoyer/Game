#include "Game.h"

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