#include "Cell.h"

Cell::Cell(SDL_Texture *texture, SDL_FRect *dim) {
    this->texture = texture;
    rect = dim;
    src_rect = nullptr;
}

Cell::Cell(SDL_Texture *texture, const SDL_FRect dim) {
    this->texture = texture;
    this->rect = new SDL_FRect(dim.x, dim.y, dim.w, dim.h);
    this->src_rect = nullptr;
}

Cell::Cell(SDL_Texture *texture, const SDL_FRect src, const SDL_FRect dim) {
    this->texture = texture;
    this->src_rect = new SDL_FRect(src.x, src.y, dim.w, dim.h);
    this->rect = new SDL_FRect(dim.x, dim.y, dim.w, dim.h);
}

Cell::Cell(SDL_Texture* texture, const float x, const float y) {
    this->texture = texture;
    this->rect = new SDL_FRect(x, y, texture->w, texture->h);
    this->src_rect = nullptr;
}

void Cell::draw(SDL_Renderer *renderer) const {
    SDL_RenderTexture(renderer, texture, src_rect, rect);
}

Cell::~Cell() {
    delete rect;
    delete src_rect;
}
