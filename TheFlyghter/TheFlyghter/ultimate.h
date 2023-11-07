#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "basic_stats.h"

using namespace std;

class ultimate : public basic_stats {
private:
	string ultimate_skin;
	int ultimate_cool_down;
	float ultimate_damage;
	int ultimate_attack_speed;
	int ultimate_extent;
	int ultimate_speed;
	int ultimate_size;
	SDL_Texture* ultimate_texture;
public:
	ultimate();
	void ultimate_change_skin(string ultimate_skin);
	void ultimate_change_cool_down(int ultimate_cool_down);
	void ultimate_change_damage(float ultimate_damage);
	void ultimate_change_attack_speed(int ultimate_attack_speed);
	void ultimate_change_extent(int ultimate_extent);
	void ultimate_change_speed(int ultimate_speed);
	void ultimate_change_size(int ultimate_size);
	int return_ultimate_cool_down();
	float return_ultimate_damage();
	int return_ultimate_attack_speed();
	int return_ultimate_extent();
	int return_ultimate_speed();
	int return_ultimate_size();
	string return_ultimate_skin();
};