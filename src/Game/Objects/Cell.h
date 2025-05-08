#ifndef CELL_H
#define CELL_H
#include  <SDL3/SDL.h>

class Cell  {
    SDL_FRect* rect = nullptr;
    SDL_FRect* src_rect = nullptr;
    SDL_Texture* texture = nullptr;

    int value = 0;
public:
    Cell() = default;
    Cell(SDL_Texture* texture, SDL_FRect* dim);
    Cell(SDL_Texture* texture, SDL_FRect dim);
    Cell(SDL_Texture* texture, SDL_FRect src, SDL_FRect dim);
    Cell(SDL_Texture* texture, float x, float y);
    void draw(SDL_Renderer* renderer) const;
    ~Cell();
};



#endif
