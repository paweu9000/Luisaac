#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "../game/window.h"


const int level[12][20] =
{
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
	{6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8},
	{6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8},
	{6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8},
	{6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8},
	{6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8},
	{6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8},
	{6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8},
	{6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8},
	{6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8},
	{6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8},
	{3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4}
};

SDL_Texture* file0 = IMG_LoadTexture(gRenderer, "tiles/0-frame.png");
SDL_Texture* file1 = IMG_LoadTexture(gRenderer, "tiles/1-frame.png");
SDL_Texture* file2 = IMG_LoadTexture(gRenderer, "tiles/3-frame.png");
SDL_Texture* file3 = IMG_LoadTexture(gRenderer, "tiles/3-frame-botleft.png");
SDL_Texture* file4 = IMG_LoadTexture(gRenderer, "tiles/3-frame-botright.png");
SDL_Texture* file5 = IMG_LoadTexture(gRenderer, "tiles/3-frame-topright.png");
SDL_Texture* file6 = IMG_LoadTexture(gRenderer, "tiles/0-frame-left.png");
SDL_Texture* file7 = IMG_LoadTexture(gRenderer, "tiles/0-frame-down.png");
SDL_Texture* file8 = IMG_LoadTexture(gRenderer, "tiles/0-frame-right.png");

SDL_Texture* levelSources[]
{
	file0, file1, file2,
	file3, file4, file5,
	file6, file7, file8
};

void createLevel()
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			SDL_Rect field = { 64 * j, 64 * i, 64, 64 };
			SDL_RenderCopy(gRenderer, levelSources[level[i][j]], NULL, &field);
		}
	}
}