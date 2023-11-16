#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Pause
{
public:
	void initialize(SDL_Renderer* renderer);
	SDL_Texture* getTexture();
	SDL_Rect getRect();
	int pause_delay;
	SDL_Texture* texture;
	SDL_Rect pause_rect;
};
