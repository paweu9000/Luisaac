#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "../game/game.h"

SDL_Texture* heart_texture = IMG_LoadTexture(gRenderer, "hpbar/graphics/heart.png");

SDL_Texture* halfheart_texture = IMG_LoadTexture(gRenderer, "hpbar/graphics/halfheart.png");

void initHpBar(int player_hp)
{
	SDL_Rect playerHpViewport;
	int vX = 1000;
	int vY = 38;
	int vW = 64;
	int vH = 64;
	int pHp = player_hp;
	while (pHp > 0) {
		if (pHp > 1)
		{
			SDL_Rect heart = { vX, vY, vW, vH };
			SDL_RenderCopy(gRenderer, heart_texture, NULL, &heart);
			vX += 72;
			pHp -= 2;
		}
		else if (pHp == 1)
		{
			SDL_Rect heart = { vX, vY, vW, vH };
			SDL_RenderCopy(gRenderer, halfheart_texture, NULL, &heart);
			vX += 72;
			pHp -= 1;
		}
	}
}