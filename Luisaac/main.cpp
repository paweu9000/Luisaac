#include <stdio.h>
#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
#include "player.h"
#include <vector>
#include "projectile.h"
#include "enemy.h"


const int16_t respawnRate = 2000;
int64_t lastSpawn = SDL_GetTicks();
const int enemyLimit = 3;

const int WIDTH = 1280;
const int HEIGHT = 768;

bool keyW = false;
bool keyA = false;
bool keyS = false;
bool keyD = false;
bool shootL = false;
bool shootR = false;
bool shootD = false;
bool shootU = false;

SDL_Window* gWindow = SDL_CreateWindow("Luisaac", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


Player player;
std::vector<Projectile> projectiles;
std::vector<Enemy> enemies;

SDL_Texture* heart_texture = IMG_LoadTexture(gRenderer, "heart.png");

SDL_Texture* halfheart_texture = IMG_LoadTexture(gRenderer, "halfheart.png");

void initHpBar()
{
	SDL_Rect playerHpViewport;
	int vX = 1000;
	int vY = 38;
	int vW = 64;
	int vH = 64;
	int pHp = player.getHp();
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

void addProjectile(Direction d)
{
	projectiles.push_back(Projectile(player.getX()+20, player.getY()+20, d, SDL_GetTicks(), gRenderer));
}

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

SDL_Texture* file0 = IMG_LoadTexture(gRenderer, "0-frame.png");
SDL_Texture* file1 = IMG_LoadTexture(gRenderer, "1-frame.png");
SDL_Texture* file2 = IMG_LoadTexture(gRenderer, "3-frame.png");
SDL_Texture* file3 = IMG_LoadTexture(gRenderer, "3-frame-botleft.png");
SDL_Texture* file4 = IMG_LoadTexture(gRenderer, "3-frame-botright.png");
SDL_Texture* file5 = IMG_LoadTexture(gRenderer, "3-frame-topright.png");
SDL_Texture* file6 = IMG_LoadTexture(gRenderer, "0-frame-left.png");
SDL_Texture* file7 = IMG_LoadTexture(gRenderer, "0-frame-down.png");
SDL_Texture * file8 = IMG_LoadTexture(gRenderer, "0-frame-right.png");

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

void movePlayer()
{
	SDL_Rect pRect = { player.getX(), player.getY(), 64, 64 };
	SDL_RenderCopy(gRenderer, player.getTexture(), NULL, &pRect);
}

void initializePlayer(SDL_Renderer* renderer)
{
	player = Player();
	player.setX(WIDTH);
	player.setY(HEIGHT);
	player.setTexture(renderer);
}

void moveEnemy()
{
	for (auto en : enemies)
	{
		SDL_Rect eRect = { en.getX(), en.getY(), 64, 64 };
		SDL_RenderCopy(gRenderer, en.getTexture(), NULL, &eRect);
	}
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

void checkMovement(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_w:
			keyW = true;
			break;
		case SDLK_s:
			keyS = true;
			break;
		case SDLK_a:
			keyA = true;
			break;
		case SDLK_d:
			keyD = true;
			break;
		}
	}
	if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_w:
			keyW = false;
			break;
		case SDLK_s:
			keyS = false;
			break;
		case SDLK_a:
			keyA = false;
			break;
		case SDLK_d:
			keyD = false;
			break;
		}
	}
}

void checkShooting(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_i:
			shootU = true;
			break;
		case SDLK_k:
			shootD = true;
			break;
		case SDLK_j:
			shootL = true;
			break;
		case SDLK_l:
			shootR = true;
			break;
		}
	}
	if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_i:
			shootU = false;
			break;
		case SDLK_k:
			shootD = false;
			break;
		case SDLK_j:
			shootL = false;
			break;
		case SDLK_l:
			shootR = false;
			break;
		}
	}
}

void shootByDirection()
{
	if (keyD && shootU) addProjectile(RU);
	else if (keyA && shootU) addProjectile(LU);
	else if (keyD && shootD) addProjectile(RD);
	else if (keyA && shootD) addProjectile(LD);
	else if (shootD) addProjectile(D);
	else if (shootL) addProjectile(L);
	else if (shootU) addProjectile(U);
	else if (shootR) addProjectile(R);
}

void handleShooting()
{
	if (projectiles.size() >= 1)
	{
		//check if last projectile is out of cooldown
		Projectile lastProj = projectiles[projectiles.size() - 1];
		if ((SDL_GetTicks() - lastProj.getLaunchTime()) / 250 > player.getProjectileSpeed())
		{
			shootByDirection();
		}
	}
	else {
		shootByDirection();
	}
}

bool checkForCollision(Projectile projectile)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (projectile.getProjectileX() <= enemies[i].getX() + 64 && projectile.getProjectileX() >= enemies[i].getX()
			&& projectile.getProjectileY() >= enemies[i].getY() && projectile.getProjectileY() <= enemies[i].getY() + 64) {
			enemies[i].getHit();
			if (enemies[i].getHp() <= 0) enemies.erase(enemies.begin() + i);
			return true;
		}
	}
	return false;
}

void moveProjectiles()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i].move();
		//delete projectile if out of bounds
		int pX = projectiles[i].getProjectileX(), pY = projectiles[i].getProjectileY();
		if (pX > 1230 || pX < 64 || pY < 64 || pY > 720)
		{
			projectiles.erase(projectiles.begin() + i);
		}
		else if (checkForCollision(projectiles[i]))
		{
			projectiles.erase(projectiles.begin() + i);
		}
		else {
			SDL_Rect projRect = { pX, pY, 16, 16 };
			SDL_RenderCopy(gRenderer, projectiles[i].getTexture(), NULL, &projRect);
		}
	}
}

void spawnEnemy()
{
	int64_t newTime = SDL_GetTicks();
	if (enemies.size() < enemyLimit && newTime - lastSpawn >= respawnRate) {
		lastSpawn = newTime;
		enemies.emplace_back(Enemy(gRenderer));
	}
}

void handleMovement()
{
	if (keyW) {
		if (keyD) {
			player.moveUpRight();
		}
		else if (keyA) {
			player.moveUpLeft();
		}
		else {
			player.moveUp();
		}
	}
	else if (keyS) {
		if (keyD) {
			player.moveDownRight();
		}
		else if (keyA) {
			player.moveDownLeft();
		}
		else {
			player.moveDown();
		}
	}
	else if (keyA) {
		player.moveLeft();
	}
	else if (keyD) {
		player.moveRight();
	}
}

void aggroPlayer()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].aggroPlayer(player.getX(), player.getY()) && SDL_GetTicks() - player.lastHitTime >= 1000)
		{
			player.getDamage();
			player.lastHitTime = SDL_GetTicks();
		}
	}
}

int main(int argc, char* args[])
{
	init();
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		SDL_RenderClear(gRenderer);
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
				break;
			}
			checkMovement(e);
			checkShooting(e);
		}
		handleMovement();
		handleShooting();
		createLevel();
		spawnEnemy();
		moveEnemy();
		moveProjectiles();
		movePlayer();
		aggroPlayer();
		initHpBar();
		SDL_RenderPresent(gRenderer);
	}
	return 0;
}

