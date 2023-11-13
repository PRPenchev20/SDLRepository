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
#include "update.h"

using namespace std;

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

        if (mouseClicked) {
            player1.switch_attack_mode();
            mouseClicked = false;
        }

        update(enemies, player1, counter, quit, renderer, bullets, mouseX, mouseY, background);
        render(enemies, player1, counter, renderer, bullets, mouseX, mouseY, background);
        SDL_Delay(1000 / FPS);
    }
    return 0;
}