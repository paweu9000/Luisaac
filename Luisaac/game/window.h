#pragma once
#include <SDL.h>
#include "../player/player.h"

const int WIDTH = 1280;
const int HEIGHT = 768;

SDL_Window* gWindow = SDL_CreateWindow("Luisaac", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

Player player;

void initializePlayer(SDL_Renderer* renderer)
{
	player = Player();
	player.setX(WIDTH);
	player.setY(HEIGHT);
	player.setTexture(renderer);
	player.setRenderer(renderer);
}

void init()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_UpdateWindowSurface(gWindow);
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) && imgFlags))
	{
		printf("Error");
	}
	initializePlayer(gRenderer);
}