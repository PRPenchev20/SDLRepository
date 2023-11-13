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

void render(vector<enemy> enemies, player player1, int counter, SDL_Renderer* renderer, vector<Bullet> bullets, int x, int y, Background& background)
{
    background.render(renderer);
    for (auto& b : bullets)
    {
        b.render(renderer);
    }
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].render(renderer);
    }
    player1.render(renderer);
    SDL_RenderPresent(renderer);
}
