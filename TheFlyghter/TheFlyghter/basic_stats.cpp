#include "basic_stats.h"
#include <SDL_image.h>

basic_stats::basic_stats() : 
    texture(nullptr), 
    skin(""), max_health(50.0f), 
    current_health(50.0f),
    attack_speed(30), 
    damage(2.0f),
    size(100), 
    pos_x(0), pos_y(50) {}

void basic_stats::loadTexture(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(skin.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void basic_stats::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { pos_x, pos_y, size, size };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void basic_stats::change_skin(std::string name) {
    skin = name;
}

void basic_stats::hit(float damage_taken) {
    current_health -= damage_taken;
}

void basic_stats::revive() {
    current_health = max_health;
}

int basic_stats::return_size() {
    return size;
}

int basic_stats::return_attack_speed() {
    return attack_speed;
}

int basic_stats::return_health() {
    return current_health;
}

bool basic_stats::touched(SDL_Rect rect) {
    if (rect.x < pos_x + size &&
        rect.x + rect.w > pos_x &&
        rect.y < pos_y + size &&
        rect.y + rect.h > pos_y)
        return true;
    else
        return false;
}
