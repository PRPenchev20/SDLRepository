#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "bullet.h"

using namespace std;

Bullet::Bullet(SDL_Renderer* renderer, int posX, int posY, int width, int height, int speed, int damage, const std::string& skin, int way, bool player_team) : posX(posX), posY(posY), width(width), height(height), speed(speed), damage(damage), skin(skin), way(way), player_team(player_team), texture(nullptr) {
    loadTexture(renderer, skin);
}

void Bullet::loadTexture(SDL_Renderer* renderer, const std::string& imagePath) {
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_Rect bulletRect = { posX, posY, width, height };
    SDL_RenderCopy(renderer, texture, nullptr, &bulletRect);
}

void Bullet::move() {
    posY -= speed * way;
}

int Bullet::returnY() {
    return posY;
}

int Bullet::return_damage() {
    return damage;
}

SDL_Rect Bullet::return_Rect() {
    SDL_Rect bulletRect = { posX, posY, width, height };
    return bulletRect;
}

bool Bullet::return_team() {
    return player_team;
}
