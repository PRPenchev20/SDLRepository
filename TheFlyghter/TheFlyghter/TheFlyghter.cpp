#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

class player
{
private:
    float max_health = 100.0f;
    float current_health = 100.0f;
    int attack_speed = 20; //The lower the faster = X renders for a attack
    float damage = 2.0f; //The lower the faster
    int size = 50;//X pixels
    string skin = "../images/bitmap.png";
    SDL_Texture* texture;
public:
    void loadTexture(SDL_Renderer* renderer, const string& imagePath)
    {
        SDL_Surface* surface = IMG_Load(imagePath.c_str());
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    void render(SDL_Renderer* renderer, int x, int y)
    {
        SDL_Rect playerRect = { x, y, size, size };
        SDL_RenderCopy(renderer, texture, NULL, &playerRect);
    }

    void hit(float damage_taken)
    {
        current_health -= damage_taken;
    }

    void revive()
    {
        current_health = max_health;
    }

    void change_skin(string name)
    {
        skin = name;
    }

    int return_size()
    {
        return size;
    }

    int return_attack_speed()
    {
        return attack_speed;
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
    string skin;
    SDL_Texture* texture;
public:
    bullet(SDL_Renderer* renderer,int posX, int posY, int width, int height, int speed ,int damage, const string& skin)
    {
        this->posX = posX;
        this->posY = posY;
        this->speed = speed;
        this->damage = damage;
        this->width = width;
        this->height = height;
        loadTexture(renderer, skin);
    }

    ~bullet()
    {
        cout << "Done";
        //SDL_DestroyTexture(texture);
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
        posY -= speed;
    }

    int returnY()
    {
        return posY;
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

void game_tick(SDL_Renderer* renderer, int& counter, vector<bullet>& bullets, player player1, int x, int y )
{
    if (counter % player1.return_attack_speed() == 0)
    {
        bullets.push_back(bullet(renderer, x, y, 5, 40, 10, 10, "../images/laser.png"));
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
 
    SDL_Window* window = SDL_CreateWindow("Player Movement", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    int mouseX, mouseY;
    int counter = 0;

    vector<bullet> bullets;

    player player1;
    player1.loadTexture(renderer, "../images/bitmap.png");
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

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](bullet& b) {
            if (b.returnY() <= 0) {
                return true;
            }
            return false;
            }), bullets.end());


        background.render(renderer);

        for (auto& b : bullets)
        {
            b.move();    
            b.render(renderer);
        }

        player1.render(renderer, mouseX - player1.return_size() / 2, mouseY - player1.return_size() / 2);
       
        game_tick(renderer, counter, bullets, player1, mouseX, mouseY);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }
    return 0;
}