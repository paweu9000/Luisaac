#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

enum Direction
{
	L, R, U, D, LU, RU, LD, RD
};

class Projectile 
{
	public:
		Projectile(int x, int y, Direction direction, uint32_t launched, SDL_Renderer* renderer);
		int getProjectileSpeed();
		int getProjectileX();
		int getProjectileY();
		uint32_t getLaunchTime();
		void move();
		SDL_Texture* getTexture();


	private:
		int speed = 3;
		int x;
		int y;
		Direction direction;
		uint32_t launched;
		SDL_Texture* graphic;
};

inline Projectile::Projectile(int x, int y, Direction direction, uint32_t launched, SDL_Renderer* renderer)
{
	this->x = x;
	this->y = y;
	this->direction = direction;
	this->launched = launched;
	this->graphic = IMG_LoadTexture(renderer, "projectiles/graphics/projectile.png");
}

inline int Projectile::getProjectileSpeed()
{
	return speed;
}

inline int Projectile::getProjectileX()
{
	return x;
}

inline int Projectile::getProjectileY()
{
	return y;
}

inline uint32_t Projectile::getLaunchTime()
{
	return this->launched;
}

inline void Projectile::move()
{
	switch (this->direction) {
	case U:
		this->y -= this->speed;
		break;
	case L:
		this->x -= this->speed;
		break;
	case D:
		this->y += this->speed;
		break;
	case R:
		this->x += this->speed;
		break;
	case LD:
		this->x -= this->speed;
		this->y += this->speed;
		break;
	case RD:
		this->x += this->speed;
		this->y += this->speed;
		break;
	case RU:
		this->x += this->speed;
		this->y -= this->speed;
		break;
	case LU:
		this->x -= this->speed;
		this->y -= this->speed;
		break;
	}
}

inline SDL_Texture* Projectile::getTexture()
{
	return graphic;
}