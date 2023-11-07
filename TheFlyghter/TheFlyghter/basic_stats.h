#pragma once
#include <SDL.h>
#include <string>

class basic_stats {
protected:
    SDL_Texture* texture;
    std::string skin;
    float max_health;
    float current_health;
    int attack_speed;
    int attack_fly_speed;
    float damage;
    int size;
    int pos_x, pos_y;

public:
    basic_stats();
    void loadTexture(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    void change_skin(std::string name);
    void hit(float damage_taken);
    void revive();
    int return_size();
    int return_attack_speed();
    int return_health();
    bool touched(SDL_Rect rect);
    float return_damage();
};
