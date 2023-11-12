#include "enemy.h"
#include <iostream>

Enemy::Enemy(SDL_Renderer* renderer)
{
	this->texture = IMG_LoadTexture(renderer, "enemy/graphics/enemy_vertical/side12.png");
	this->x = rand() % 1137 + 64;
	this->y = rand() % 600 + 64;
	this->tSpawn = SDL_GetTicks();
	this->sleep = true;
	this->renderer = renderer;
	generateTextures();
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

	bool newFrame = (SDL_GetTicks() - this->lastFrameTick) > 90;

	if (abs_distance < 1200)
	{
		if (dist.x > 0) {
			this->x -= this->speed;
			if (newFrame) this->texture = IMG_LoadTexture(renderer, horizontal_textures[horizontal_t].c_str());
			horizontal_t++;
		}
		else if (dist.y > 0) {
			this->y -= this->speed;
			if (newFrame) this->texture = IMG_LoadTexture(renderer, vertical_textures[vertical_t].c_str());
			vertical_t++;
		}
		else if (dist.x < 0) {
			this->x += this->speed;
			if (newFrame) this->texture = IMG_LoadTexture(renderer, horizontal_textures[horizontal_t].c_str());
			horizontal_t++;
		}
		else if (dist.y < 0) {
			this->y += this->speed;
			if (newFrame) this->texture = IMG_LoadTexture(renderer, vertical_textures[vertical_t].c_str());
			vertical_t++;
		}
		if (newFrame) this->lastFrameTick = SDL_GetTicks();
		if (horizontal_textures.size() == horizontal_t) this->horizontal_t = 0;
		if (vertical_textures.size() == vertical_t) this->vertical_t = 0;
	}

	return (abs_distance < 40);
}

void Enemy::getHit()
{
	this->hp -= 1;
	if (hp <= 0) std::cout << "Dead\n";
}

void Enemy::generateTextures()
{
	std::string path = "enemy/graphics/enemy_vertical";
	std::vector<std::string> frames;
	for (const auto& entry : std::filesystem::directory_iterator(path)) frames.emplace_back(entry.path().string());
	sort(frames.begin(), frames.end());
	this->vertical_textures = frames;

	std::string path1 = "enemy/graphics/enemy_horizontal";
	std::vector<std::string> frames1;
	for (const auto& entry : std::filesystem::directory_iterator(path1)) frames1.emplace_back(entry.path().string());
	sort(frames1.begin(), frames1.end());
	this->horizontal_textures = frames1;
}