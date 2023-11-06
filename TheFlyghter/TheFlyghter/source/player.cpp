#include "player.h"

player::player() : skin("../images/ship_skin2.png") {
    change_skin(skin);
}

void player::move(int x, int y) {
    pos_x = x;
    pos_y = y;
}

SDL_Rect player::return_Rect() {
    SDL_Rect rect = { pos_x, pos_y, size, size };
    return rect;
}
