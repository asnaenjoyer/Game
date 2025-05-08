#ifndef GAME_H
#define GAME_H
#include "../MyAPI/App.h"
#include "Objects/Grid.h"


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



#endif //GAME_H
