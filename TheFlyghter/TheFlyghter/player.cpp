#include "player.h"
#include "ultimate.h"
using namespace std;
player::player() : skin("../images/ship_skin2.png"), attack_switch(false)
{
    ultimate myUltimate();
    change_skin(skin);
}

void player::move(int x, int y) {
    pos_x = x;
    pos_y = y;
}

void player::switch_attack_mode()
{
    if (attack_switch == true)
        attack_switch = false;
    else
        attack_switch = true;
}

bool player::return_attack_mode()
{
    return attack_switch;
}

SDL_Rect player::return_Rect() {
    SDL_Rect rect = { pos_x, pos_y, size, size };
    return rect;
}
