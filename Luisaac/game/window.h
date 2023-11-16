#pragma once
#include <SDL.h>
#include "../player/player.h"
#include "score.h"
#include "pause.h"
#include "settings.h"
#include "deathscreen.h"

Settings settings = Settings();

const int WIDTH = settings.WIDTH;
const int HEIGHT = settings.HEIGHT;

//enemy respawn rate
int respawnRate = settings.respawnRate;

//enemy last spawn
int lastSpawn = SDL_GetTicks();

int enemyLimit = settings.enemyLimit;

bool keyW = false;
bool keyA = false;
bool keyS = false;
bool keyD = false;
bool shootL = false;
bool shootR = false;
bool shootD = false;
bool shootU = false;

bool paused = false;

int timer = SDL_GetTicks();

std::vector<Projectile> projectiles;
std::vector<Enemy> enemies;

SDL_Window* gWindow = SDL_CreateWindow("Luisaac", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

Player player;
Score score = Score(gRenderer, 24, { 0xFF, 0xFF, 0xFF, 0xFF });
Pause pause;
DeathScreen deathScreen;

int player_death_time = NULL;

void initializePlayer(SDL_Renderer* renderer)
{
	player = Player();
	player.setX(WIDTH);
	player.setY(HEIGHT);
	player.setTexture(renderer);
	player.setRenderer(renderer);
}

void initializeScore()
{
	score.loadFont();
}

void init()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_UpdateWindowSurface(gWindow);
	int imgFlags = IMG_INIT_PNG;
	if (TTF_Init() == -1) printf("TTF Error");
	if (!(IMG_Init(imgFlags) && imgFlags))
	{
		printf("Error");
	}
	initializePlayer(gRenderer);
	initializeScore();
	pause.initialize(gRenderer);
	deathScreen.initialize(gRenderer);
}

void resetScore()
{
	score = Score(gRenderer, 24, { 0xFF, 0xFF, 0xFF, 0xFF });
	score.loadFont();
}

void resetGame()
{
	initializePlayer(gRenderer);
	resetScore();
	enemyLimit = settings.enemyLimit;
	timer = SDL_GetTicks();
	projectiles.erase(projectiles.begin(), projectiles.end());
	enemies.erase(enemies.begin(), enemies.end());
	player_death_time = NULL;
}