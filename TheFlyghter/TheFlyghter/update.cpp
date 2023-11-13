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

void update(vector<enemy>& enemies, player& player1, int& counter, bool& quit, SDL_Renderer* renderer, vector<Bullet>& bullets, int& x, int& y, Background& background)
{
    background.scroll();

    bullets.erase(remove_if(bullets.begin(), bullets.end(), [&](Bullet& b) {
        if (b.returnY() <= 0) {
            return true;
        }
        else if (player1.touched(b.return_Rect()) == true and b.return_team() == false)
        {
            player1.hit(b.return_damage());
            return true;
        }
        for (int i = 0; i < enemies.size(); i++)
            if (enemies[i].touched(b.return_Rect()) == true and b.return_team() == true)
            {
                enemies[i].hit(b.return_damage());
                return true;
            }
        return false;
        }), bullets.end());
    player1.move(x - player1.return_size() / 2, y - player1.return_size() / 2);
    if (player1.return_attack_mode() == false and counter % player1.return_attack_speed() == 0)
    {
        bullets.push_back(Bullet(renderer, x - player1.return_ultimate_size() / 2, y, 20, player1.return_ultimate_size(), 10, player1.return_damage(), "../images/laser1.png", 1, true));
    }
    else if (player1.return_attack_mode() == true and counter % player1.return_ultimate_attack_speed() == 0)
    {
        bullets.push_back(Bullet(renderer, x - player1.return_ultimate_size() / 2, y, player1.return_ultimate_size(), player1.return_ultimate_size() * 2, player1.return_ultimate_speed(), player1.return_ultimate_damage(), player1.return_ultimate_skin(), 1, true));
    }

    for (int i = 0; i < enemies.size(); i++)
        if (counter % enemies[i].return_attack_speed() == 0)
        {
            bullets.push_back(Bullet(renderer, enemies[i].return_x() + enemies[i].return_size() / 2, enemies[i].return_y() + enemies[i].return_size() / 2, 20, 40, 10, enemies[i].return_damage(), "../images/laser1.png", -1, false));
        }

    if (counter % 100 == 0)
    {
        enemy n;
        enemies.push_back(n);
        enemies[enemies.size() - 1].loadTexture(renderer);
    }
    enemies.erase(remove_if(enemies.begin(), enemies.end(), [&](enemy& b) {
        if (b.return_health() <= 0) {
            return true;
        }

        return false;
        }), enemies.end());
    for (auto& b : bullets)
    {
        b.move();
    }
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].AI_movement_per_tick(player1.return_Rect(), enemies);
    }
    if (player1.return_health() <= 0)
    {
        cout << "score: " << counter << endl;
        cout << "you lost";
        quit = true;
    }

    counter++;
}