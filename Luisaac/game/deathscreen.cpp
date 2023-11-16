#include "deathscreen.h"

void DeathScreen::initialize(SDL_Renderer* renderer)
{
	this->texture = IMG_LoadTexture(renderer, "game/pause/deathscreen.png");
	this->pause_rect = { 340, 128, 600, 600 };
	this->pause_delay = SDL_GetTicks();
}