#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "basic_stats.h"
#include "enemy.h"
#include "player.h"
#include "bullet.h"
#include "background.h"
#include "constants.h"
#include "render.h"

using namespace std;

void update(vector<enemy>& enemies, player& player1, int& counter, bool& quit, SDL_Renderer* renderer, vector<Bullet>& bullets, int& x, int& y, Background& background);