#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include <memory>
#include <SDL3/SDL.h>

class ImageLoader {
    std::shared_ptr<SDL_Renderer> renderer;
public:
    ImageLoader(const std::shared_ptr<SDL_Renderer> &renderer);

    ImageLoader(const ImageLoader&) = delete;

    SDL_Texture* loadTexture(const char* path) const;
};



#endif
