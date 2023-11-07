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

void game_tick(SDL_Renderer* renderer, int& counter, vector<Bullet>& bullets, vector<enemy>& enemies, player player1, int x, int y)
{
    if (player1.return_attack_mode() == false and counter % player1.return_attack_speed() == 0)
    {
        bullets.push_back(Bullet(renderer, x - player1.return_ultimate_size() / 2, y, 20, player1.return_ultimate_size(), 10, player1.return_damage(), "../images/laser1.png", 1, true));
    }
    else if (player1.return_attack_mode() == true and counter % player1.return_ultimate_attack_speed() == 0)
    {
        bullets.push_back(Bullet(renderer, x - player1.return_ultimate_size() / 2, y, player1.return_ultimate_size(), player1.return_ultimate_size() * 2, player1.return_ultimate_speed(), player1.return_ultimate_damage(), player1.return_ultimate_skin(), 1, true));
    }

    for(int i = 0; i < enemies.size(); i++)
    if (counter % enemies[i].return_attack_speed() == 0)
    {
        bullets.push_back(Bullet(renderer, enemies[i].return_x() + enemies[i].return_size() / 2, enemies[i].return_y() + enemies[i].return_size() / 2, 20, 40, 10, enemies[i].return_damage(), "../images/laser1.png", -1, false));
    }

    if (counter % 100 == 0)
    {
        enemy n;
        enemies.push_back(n);
        enemies[enemies.size()-1].loadTexture(renderer);
    }
    counter++;
}


int main(int argc, char* argv[])  
{
    const int FPS = 60;
    float frameTime = 0;
    int prevTime = 0;
    int currentTime = 0;
    float deltaTime = 0;
    float moveSpeed = 200.0f;
 
    SDL_Window* window = SDL_CreateWindow("SDL App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    int mouseX, mouseY;
    int counter = 1;      

    vector<Bullet> bullets;
    vector<enemy> enemies;
    enemy n;

    SDL_Event event;
    bool mouseClicked = false;

    player player1;
    player1.loadTexture(renderer);

    enemies.push_back(n);
    enemies[0].loadTexture(renderer);

    Background background(renderer, "../images/background.png", 2);
    
    while (!quit)
    {
        prevTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f;
        SDL_RenderClear(renderer);
        SDL_Event e;

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                // Mouse button was clicked
                // Perform the desired action here
                mouseClicked = true;
            }
        }

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_GetMouseState(&mouseX, &mouseY);  

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
            for(int i = 0; i < enemies.size(); i++)
            if (enemies[i].touched(b.return_Rect()) == true and b.return_team() == true)
            {
                enemies[i].hit(b.return_damage());
                return true;
            }
            return false;
            }), bullets.end());

        enemies.erase(remove_if(enemies.begin(), enemies.end(), [&](enemy& b) {
            if (b.return_health() <= 0) {
                return true;
            }
           
            return false;
            }), enemies.end());

        background.render(renderer);

        for (auto& b : bullets)
        { 
            b.move();
            b.render(renderer);
        }

        player1.move(mouseX - player1.return_size() / 2, mouseY - player1.return_size() / 2);
        player1.render(renderer);   
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].AI_movement_per_tick(player1.return_Rect(), enemies);
            enemies[i].render(renderer);
        }
        if (player1.return_health() <= 0)
        {
            cout << "score: " << counter << endl ;
            cout << "you lost";
            quit = true;
        }

        

        // Game logic
        if (mouseClicked) {
            player1.switch_attack_mode();
            mouseClicked = false;
        }

        game_tick(renderer, counter, bullets,enemies, player1, mouseX, mouseY);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }
    return 0;
}