#pragma once
#include <string>
#include <SDL.h>
#include "basic_stats.h"

using namespace std;

class player : public basic_stats
{
private:
    string skin;
public:
    player();
    void move(int x, int y);
    SDL_Rect return_Rect();
};