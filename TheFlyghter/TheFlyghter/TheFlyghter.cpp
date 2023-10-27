#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1920;  // Desired width
const int SCREEN_HEIGHT = 1080; // Desired height

class basic_stats
{
protected:
    
    SDL_Texture* texture;
    string skin = "";
    float max_health = 100.0f;
    float current_health = 100.0f;
    int attack_speed = 20; //The lower the faster = X renders for a attack
    float damage = 2.0f; //The lower the faster
    int size = 100;//X pixels
    int pos_x = 0, pos_y = 50;

public:
    void loadTexture(SDL_Renderer* renderer)
    {
        SDL_Surface* surface = IMG_Load(skin.c_str());
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    void render(SDL_Renderer* renderer)
    {
        SDL_Rect rect = { pos_x, pos_y, size, size };
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void change_skin(string name)
    {
        skin = name;
    }

    void hit(float damage_taken)
    {
        current_health -= damage_taken;
    }

    void revive()
    {
        current_health = max_health;
    }

    int return_size()
    {
        return size;
    }

    int return_attack_speed()
    {
        return attack_speed;
    }

    int return_health()
    {
        return current_health;
    }

    bool touched(SDL_Rect rect)
    {
        if (rect.x < pos_x + size &&
            rect.x + rect.w > pos_x &&
            rect.y < pos_y + size &&
            rect.y + rect.h > pos_y)
            return true;
        else
            return false;
    }
};

class enemy : public basic_stats
{
private:
    string skin = "../images/bitmap.png";//basic skin
    int speed = 2;
public:
    enemy()
    {
        change_skin(this->skin);
    }

    void AI_movement_per_tick(SDL_Rect rect)
    {
        if (rect.x > pos_x)
            pos_x+=speed;
        else
            pos_x-=speed;
    }

    int return_x()
    {
        return pos_x;
    }
     
    int return_y()
    {
        return pos_y;
    }

    int return_size()
    {
        return size;
    }
};

class player : public basic_stats
{
private:
    string skin = "../images/ship_skin2.png";//basic skin
public:   
    player()
    {
        change_skin(this->skin);
    }
    void move(int x, int y)
    {
        pos_x = x;
        pos_y = y;
    }
    SDL_Rect return_Rect()
    {
        SDL_Rect rect = { pos_x, pos_y, size, size };
        return rect;
    }
};

class bullet
{
private:
    int posX;
    int posY;
    int width;
    int height;
    int speed;// X pixels per frame
    int damage;
    int way;
    bool player_team;
    string skin;
    SDL_Texture* texture;
public:
    bullet(SDL_Renderer* renderer,int posX, int posY, int width, int height, int speed ,int damage, const string& skin, int way, bool player_team)//!!!the way can be implemented only by 1 or -1. 1 means its going up -1 means its going down
    {
        this->posX = posX;
        this->posY = posY;
        this->speed = speed;
        this->damage = damage;
        this->width = width;
        this->height = height;
        this->way = way;
        this->player_team = player_team;
        loadTexture(renderer, skin);
    }

    void loadTexture(SDL_Renderer* renderer, const string& imagePath)
    {
        SDL_Surface* surface = IMG_Load(imagePath.c_str());
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    void render(SDL_Renderer* renderer)
    {
        SDL_Rect bulletRect = { posX, posY, width, height };
        SDL_RenderCopy(renderer, texture, NULL, &bulletRect);
    }

    void move()
    {
        posY -= speed * way;
    }

    int returnY()
    {
        return posY;
    }

    int return_damage()
    {
        return damage;
    }

    SDL_Rect return_Rect()
    {
        SDL_Rect bulletRect = { posX, posY, width, height };
        return bulletRect;
    }

    bool return_team()
    {
        return player_team;
    }
};

class Background {
private:
    SDL_Texture* texture;
    int scrollSpeed;
    int yPos1, yPos2;

public:
    Background(SDL_Renderer* renderer, const string& imagePath, int speed) {
        SDL_Surface* surface = IMG_Load(imagePath.c_str());
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        yPos1 = 0;
        yPos2 = -SCREEN_HEIGHT;
        scrollSpeed = speed;
    }

    ~Background() {
        SDL_DestroyTexture(texture);
    }

    void scroll() {
        yPos1 += scrollSpeed;
        yPos2 += scrollSpeed;

        if (yPos1 >= SCREEN_HEIGHT) {
            yPos1 = -SCREEN_HEIGHT;
        }
        if (yPos2 >= SCREEN_HEIGHT) {
            yPos2 = -SCREEN_HEIGHT;
        }
    }

    void render(SDL_Renderer* renderer) {
        SDL_Rect destRect1 = { -5, yPos1, SCREEN_WIDTH + 10, SCREEN_HEIGHT + 10 };
        SDL_Rect destRect2 = { -5, yPos2, SCREEN_WIDTH + 10, SCREEN_HEIGHT + 10 };

        SDL_RenderCopy(renderer, texture, NULL, &destRect1);
        SDL_RenderCopy(renderer, texture, NULL, &destRect2);
    }
};

void game_tick(SDL_Renderer* renderer, int& counter, vector<bullet>& bullets, vector<enemy>& enemies, player player1, int x, int y)
{
    if (counter % player1.return_attack_speed() == 0)
    {
        bullets.push_back(bullet(renderer, x, y, 20, 40, 10, 10, "../images/laser1.png", 1, true));
    }

    for(int i = 0; i < enemies.size(); i++)
    if (counter % enemies[i].return_attack_speed() == 0)
    {
        bullets.push_back(bullet(renderer, enemies[i].return_x() + enemies[i].return_size() / 2, enemies[i].return_y() + enemies[i].return_size() / 2, 20, 40, 10, 10, "../images/laser1.png", -1, false));
    }

    if (counter % 1000 == 0)
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
    int counter = 0;      

    vector<bullet> bullets;
    vector<enemy> enemies;
    enemy n;

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
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_GetMouseState(&mouseX, &mouseY);  

        background.scroll();

        bullets.erase(remove_if(bullets.begin(), bullets.end(), [&](bullet& b) {
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
            enemies[i].AI_movement_per_tick(player1.return_Rect());
            enemies[i].render(renderer);
        }

        game_tick(renderer, counter, bullets,enemies, player1, mouseX, mouseY);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }
    return 0;
}