#include "background.h"
#include "constants.h"

Background::Background(SDL_Renderer* renderer, const std::string& imagePath, int speed) : texture(nullptr), yPos1(0), yPos2(-SCREEN_HEIGHT), scrollSpeed(speed) {
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Background::~Background() {
    SDL_DestroyTexture(texture);
}

void Background::scroll() {
    yPos1 += scrollSpeed;
    yPos2 += scrollSpeed;

    if (yPos1 >= SCREEN_HEIGHT) {
        yPos1 = -SCREEN_HEIGHT;
    }
    if (yPos2 >= SCREEN_HEIGHT) {
        yPos2 = -SCREEN_HEIGHT;
    }
}

void Background::render(SDL_Renderer* renderer) {
    SDL_Rect destRect1 = { -5, yPos1, SCREEN_WIDTH + 10, SCREEN_HEIGHT + 10 };
    SDL_Rect destRect2 = { -5, yPos2, SCREEN_WIDTH + 10, SCREEN_HEIGHT + 10 };

    SDL_RenderCopy(renderer, texture, nullptr, &destRect1);
    SDL_RenderCopy(renderer, texture, nullptr, &destRect2);
}
