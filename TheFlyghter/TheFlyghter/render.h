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

using namespace std;

void render(vector<enemy> enemies, player player1, int counter, SDL_Renderer* renderer, vector<Bullet> bullets, int x, int y, Background& background);
