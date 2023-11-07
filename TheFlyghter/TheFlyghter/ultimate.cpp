#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "basic_stats.h"
#include "ultimate.h"

using namespace std;

ultimate::ultimate() : ultimate_skin("../images/laser2.png"), ultimate_cool_down(10), ultimate_damage(2.5f), ultimate_attack_speed(1), ultimate_extent(4), ultimate_speed(80), ultimate_size(40), ultimate_texture(nullptr)
{
}
void ultimate::ultimate_change_skin(string ultimate_skin)
{
	this->ultimate_skin = ultimate_skin;
}
void ultimate::ultimate_change_cool_down(int cool_down)
{
	this->ultimate_cool_down = ultimate_cool_down;
}
void ultimate::ultimate_change_damage(float ultimate_damage)
{
	this->ultimate_damage = ultimate_damage;
}
void ultimate::ultimate_change_attack_speed(int ultimate_attack_speed)
{
	this->ultimate_attack_speed = ultimate_attack_speed;
}
void ultimate::ultimate_change_extent(int ultimate_extent)
{
	this->ultimate_extent = ultimate_extent;
}
void ultimate::ultimate_change_speed(int ultimate_speed)
{
	this->ultimate_speed = ultimate_speed;
}
void ultimate::ultimate_change_size(int ultimate_size)
{
	this->ultimate_size = ultimate_size;
}
int ultimate::return_ultimate_cool_down()
{
	return ultimate_cool_down;
}
float ultimate::return_ultimate_damage()
{
	return ultimate_damage;
}
int ultimate::return_ultimate_attack_speed()
{
	return ultimate_attack_speed;
}
int ultimate::return_ultimate_extent()
{
	return ultimate_extent;
}
int ultimate::return_ultimate_speed()
{
	return ultimate_speed;
}
int ultimate::return_ultimate_size()
{
	return ultimate_size;
}
string ultimate::return_ultimate_skin()
{
	return ultimate_skin;
}