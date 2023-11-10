#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>

#ifndef ENEMY_H

struct Vector {
	int x;
	int y;
};

class Enemy {
public:
	Enemy(SDL_Renderer* renderer);
	int getHp() const;
	SDL_Renderer* renderer;
	int getX() const;
	int getY() const;
	SDL_Texture* getTexture() const;
	bool aggroPlayer(int x, int y);
	void getHit();
	void generateTextures();
private:
	SDL_Texture* texture;
	int hp = 10;
	bool sleep;
	uint16_t tSpawn;
	int speed = 1;
	int attack_dmg = 1;
	int x;
	int y;
	int lastFrameTick = SDL_GetTicks();
	int vertical_t = 0;
	int horizontal_t = 0;
	std::vector<std::string> horizontal_textures;
	std::vector<std::string> vertical_textures;
};

#endif // !ENEMY_H

