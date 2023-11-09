#pragma once
#include <SDL.h>
#include <SDL_image.h>
#ifndef ENEMY_H

struct Vector {
	int x;
	int y;
};

class Enemy {
public:
	Enemy(SDL_Renderer* renderer);
	int getHp() const;
	int getX() const;
	int getY() const;
	SDL_Texture* getTexture() const;
	bool aggroPlayer(int x, int y);
	void getHit();
private:
	SDL_Texture* texture;
	int hp = 10;
	bool sleep;
	uint16_t tSpawn;
	int speed = 1;
	int attack_dmg = 1;
	int x;
	int y;
};

#endif // !ENEMY_H

