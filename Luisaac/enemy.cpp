#include "enemy.h"
#include <iostream>

Enemy::Enemy(SDL_Renderer* renderer)
{
	this->texture = IMG_LoadTexture(renderer, "enemy.png");
	this->x = rand() % 1137 + 64;
	this->y = rand() % 600 + 64;
	this->tSpawn = SDL_GetTicks();
	this->sleep = true;
}

int Enemy::getHp() const
{
	return this->hp;
}

SDL_Texture* Enemy::getTexture() const
{
	return this->texture;
}

int Enemy::getX() const
{
	return this->x;
}

int Enemy::getY() const
{
	return this->y;
}

bool Enemy::aggroPlayer(int x, int y)
{
	if (SDL_GetTicks() - this->tSpawn >= 2000) this->sleep = false;
	if (sleep) return false;
	Vector dist;
	dist.x = this->x - x;
	dist.y = this->y - y;

	double abs_distance = sqrt(dist.x * dist.x) + sqrt(dist.y * dist.y);

	if (abs_distance < 700)
	{
		if (dist.x > 0) this->x -= this->speed;
		if (dist.y > 0) this->y -= this->speed;
		if (dist.x < 0) this->x += this->speed;
		if (dist.y < 0) this->y += this->speed;
	}

	return (abs_distance < 20);
}

void Enemy::getHit()
{
	this->hp -= 1;
	if (hp <= 0) std::cout << "Dead\n";
}