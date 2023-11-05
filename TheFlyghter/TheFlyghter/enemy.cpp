#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "basic_stats.h"
#include "enemy.h"

using namespace std;

enemy::enemy() : skin("../images/bitmap.png"), speed(2) {
    change_skin(skin);
}

void enemy::AI_movement_per_tick(SDL_Rect rect, const vector<enemy>& n) {
    bool flag = false;

    if (flag == false)
        if (rect.x > pos_x)
            pos_x += speed;
        else
            pos_x -= speed;
}

int enemy::return_x() {
    return pos_x;
}

int enemy::return_y() {
    return pos_y;
}

int enemy::return_size() {
    return size;
}
