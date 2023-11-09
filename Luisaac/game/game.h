#pragma once
#include <SDL.h>
#include "../level/level.h"
#include "../hpbar/hpbar.h"
#include "window.h"

//enemy respawn rate
const int16_t respawnRate = 2000;

//enemy last spawn
int64_t lastSpawn = SDL_GetTicks();

int enemyLimit = 3;

bool keyW = false;
bool keyA = false;
bool keyS = false;
bool keyD = false;
bool shootL = false;
bool shootR = false;
bool shootD = false;
bool shootU = false;



std::vector<Projectile> projectiles;
std::vector<Enemy> enemies;

void addProjectile(Direction d)
{
	projectiles.push_back(Projectile(player.getX() + 20, player.getY() + 20, d, SDL_GetTicks(), gRenderer));
}

void movePlayer()
{
	SDL_Rect pRect = { player.getX(), player.getY(), 64, 64 };
	SDL_RenderCopy(gRenderer, player.getTexture(), NULL, &pRect);
}

void moveEnemy()
{
	for (auto en : enemies)
	{
		SDL_Rect eRect = { en.getX(), en.getY(), 64, 64 };
		SDL_RenderCopy(gRenderer, en.getTexture(), NULL, &eRect);
	}
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

void runGame()
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
		initHpBar(player.getHp());
		SDL_RenderPresent(gRenderer);
	}
}
