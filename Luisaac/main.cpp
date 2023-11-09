#include <stdio.h>
#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
#include "player/player.h"
#include <vector>
#include "projectiles/projectile.h"
#include "enemy/enemy.h"
#include "game/game.h"
#include "level/level.h"
#include "hpbar/hpbar.h"

int main(int argc, char* args[])
{
	runGame();
	return 0;
}

