#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Player
{
public:
	Player();
	void moveUp();
	void moveRight();
	void moveDown();
	void moveLeft();
	void moveDownLeft();
	void moveDownRight();
	void moveUpRight();
	void moveUpLeft();
	void setX(int width);
	void setY(int height);
	void setTexture(SDL_Renderer* renderer);
	int getX();
	int getY();
	int getHp();
	void getDamage();
	int getProjectileSpeed();
	SDL_Texture* getTexture();

	uint16_t lastHitTime = SDL_GetTicks();
private:
	int x;
	int y;
	int playerSpeed = 2;
	int projectileSpeed = 1;
	int hp = 6;
	SDL_Texture* playerTexture;

};

Player::Player()
{
	x = NULL;
	y = NULL;
	playerTexture = NULL;
}

void Player::setTexture(SDL_Renderer* renderer)
{
	playerTexture = IMG_LoadTexture(renderer, "player/graphics/player.png");
}

void Player::setX(int width)
{
	x = width / 2;
}

int Player::getHp()
{
	return this->hp;
}

void Player::getDamage()
{
	this->hp -= 1;
}

void Player::setY(int height)
{
	y = height / 2;
}

SDL_Texture* Player::getTexture()
{
	return playerTexture;
}

int Player::getProjectileSpeed()
{
	return this->projectileSpeed;
}

int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

void Player::moveUp()
{
	if (y > 64) y -= playerSpeed;
}

void Player::moveUpRight()
{
	if (y > 64 and 1150 > x)
	{
		y -= playerSpeed;
		x += playerSpeed;
	}
}

void Player::moveUpLeft()
{
	if (y > 64 and x > 64)
	{
		y -= playerSpeed;
		x -= playerSpeed;
	}
}

void Player::moveDown()
{
	if (y < 640) y += playerSpeed;
}

void Player::moveDownLeft()
{
	if (y < 640 and x > 64)
	{
		y += playerSpeed;
		x -= playerSpeed;
	}
}

void Player::moveDownRight()
{
	if (y < 640 and 1150 > x)
	{
		y += playerSpeed;
		x += playerSpeed;
	}
}

void Player::moveLeft()
{
	if (x > 64) x -= playerSpeed;
}

void Player::moveRight()
{
	if (1150 > x) x += playerSpeed;
}
