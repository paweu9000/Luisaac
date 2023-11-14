#include "pause.h"

void Pause::initialize(SDL_Renderer* renderer)
{
	this->texture = IMG_LoadTexture(renderer, "game/pause/pause.png");
	this->pause_rect = { 340, 128, 600, 600 };
	this->pause_delay = SDL_GetTicks();
}

SDL_Texture* Pause::getTexture()
{
	return this->texture;
}

SDL_Rect Pause::getRect()
{
	return this->pause_rect;
}