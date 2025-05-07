#include "ImageLoader.h"
#include <SDL3_image/SDL_image.h>

ImageLoader::ImageLoader(const std::shared_ptr<SDL_Renderer> &renderer) {
    this->renderer = renderer;
}

SDL_Texture* ImageLoader::loadTexture(const char *path) const {
    if (!renderer) {
        SDL_Log("Renderer is not set!");
        return nullptr;
    }

    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("Failed to load image %s: %s", path);
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        SDL_Log("Failed to create texture from %s: %s", path, SDL_GetError());
        return nullptr;
    }
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    return texture;
}
