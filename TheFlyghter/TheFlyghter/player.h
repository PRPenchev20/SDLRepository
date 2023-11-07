#pragma once
#include <string>
#include <SDL.h>
#include "basic_stats.h"
#include "ultimate.h"

using namespace std;

class player : public ultimate
{
private:
    string skin;
    bool attack_switch; //false means the normal attack
public:
    player();
    void move(int x, int y);
    void switch_attack_mode();
    bool return_attack_mode();
    SDL_Rect return_Rect();
};