#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Background {
private:
    SDL_Texture* texture;
    int scrollSpeed;
    int yPos1, yPos2;

public:
    Background(SDL_Renderer* renderer, const std::string& imagePath, int speed);
    ~Background();

    void scroll();
    void render(SDL_Renderer* renderer);
};
