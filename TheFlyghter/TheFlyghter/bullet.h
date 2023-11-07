#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Bullet {
private:
    int posX;
    int posY;
    int width;
    int height;
    int speed; // X pixels per frame
    float damage;
    int way;
    bool player_team;
    std::string skin;
    SDL_Texture* texture;

public:
    Bullet(SDL_Renderer* renderer, int posX, int posY, int width, int height, int speed, float damage, const std::string& skin, int way, bool player_team);

    void loadTexture(SDL_Renderer* renderer, const std::string& imagePath);
    void render(SDL_Renderer* renderer);
    void move();
    int returnY();
    int return_damage();
    SDL_Rect return_Rect();
    bool return_team();
};
