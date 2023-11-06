#pragma once
#include "basic_stats.h"

class enemy : public basic_stats {
private:
    std::string skin;
    int speed;

public:
    enemy();
    void AI_movement_per_tick(SDL_Rect rect, const std::vector<enemy>& n);
    int return_x();
    int return_y();
    int return_size();
};
