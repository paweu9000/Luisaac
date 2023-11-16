#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

enum MoveSide
{
	LEFT, UP, RIGHT, DOWN
};

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
	void animateDeath();
	SDL_Texture* getTexture();
	void setRenderer(SDL_Renderer* renderer);
	int lastHitTime = SDL_GetTicks();
	bool isDead = false;
private:
	int x;
	int y;
	int playerSpeed = 2;
	int projectileSpeed = 1;
	int hp = 6;
	SDL_Texture* playerTexture;
	int last_frame;
	SDL_Renderer* gRenderer;
	std::vector<std::string> playerdeathprites = { "player/graphics/playerdeath/death1.png",
		"player/graphics/playerdeath/death2.png",  "player/graphics/playerdeath/death3.png", "player/graphics/playerdeath/death4.png" };
	std::vector<std::string> playerrightsprites = { "player/graphics/playerright/playerright1.png",
		"player/graphics/playerright/playerright2.png",  "player/graphics/playerright/playerright3.png" };
	std::vector<std::string> playerleftsprites = { "player/graphics/playerleft/playerleft1.png",
		"player/graphics/playerleft/playerleft2.png",  "player/graphics/playerleft/playerleft3.png" };
	std::vector<std::string> playerupsprites = { "player/graphics/playerup/playerup1.png",
		"player/graphics/playerup/playerup2.png",  "player/graphics/playerup/playerup3.png" };
	std::vector<std::string> playerdownsprites = { "player/graphics/playerdown/playerdown1.png",
		"player/graphics/playerdown/playerdown2.png",  "player/graphics/playerdown/playerdown3.png" };
	std::vector<int> current_frame = { 0, 0, 0, 0, 0 };
	void changeFrame(MoveSide side);
};

Player::Player()
{
	x = NULL;
	y = NULL;
	playerTexture = NULL;
	last_frame = SDL_GetTicks();
}

void Player::setTexture(SDL_Renderer* renderer)
{
	playerTexture = IMG_LoadTexture(renderer, "player/graphics/playerdown/playerdown2.png");
}

void Player::setX(int width)
{
	x = width / 2;
}

void Player::setRenderer(SDL_Renderer* renderer)
{
	this->gRenderer = renderer;
}

void Player::animateDeath()
{
	int time = SDL_GetTicks();
	if (time - last_frame < 100) return;
	last_frame = time;
	this->playerTexture = IMG_LoadTexture(gRenderer, playerdeathprites[current_frame[4]].c_str());
	if (current_frame[4] == 3) return;
	current_frame[4] += 1;
}

void Player::changeFrame(MoveSide side)
{
	if (SDL_GetTicks() - last_frame < 150) return;
	switch (side)
	{
	case UP:
		this->playerTexture = IMG_LoadTexture(gRenderer, playerupsprites[current_frame[0]].c_str());
		current_frame[0] += 1;
		break;
	case LEFT:
		this->playerTexture = IMG_LoadTexture(gRenderer, playerleftsprites[current_frame[1]].c_str());
		current_frame[1] += 1;
		break;
	case RIGHT:
		this->playerTexture = IMG_LoadTexture(gRenderer, playerrightsprites[current_frame[2]].c_str());
		current_frame[2] += 1;
		break;
	case DOWN:
		this->playerTexture = IMG_LoadTexture(gRenderer, playerdownsprites[current_frame[3]].c_str());
		current_frame[3] += 1;
		break;
	}
	this->last_frame = SDL_GetTicks();
	for (int i = 0; i < current_frame.size(); i++) {
		if (current_frame[i] >= 2) current_frame[i] = 0;
	}
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
	changeFrame(UP);
}

void Player::moveUpRight()
{
	if (y > 64 and 1150 > x)
	{
		y -= playerSpeed;
		x += playerSpeed;
	}
	changeFrame(UP);
}

void Player::moveUpLeft()
{
	if (y > 64 and x > 64)
	{
		y -= playerSpeed;
		x -= playerSpeed;
	}
	changeFrame(UP);
}

void Player::moveDown()
{
	if (y < 640) y += playerSpeed;
	changeFrame(DOWN);
}

void Player::moveDownLeft()
{
	if (y < 640 and x > 64)
	{
		y += playerSpeed;
		x -= playerSpeed;
	}
	changeFrame(DOWN);
}

void Player::moveDownRight()
{
	if (y < 640 and 1150 > x)
	{
		y += playerSpeed;
		x += playerSpeed;
	}
	changeFrame(DOWN);
}

void Player::moveLeft()
{
	if (x > 64) x -= playerSpeed;
	changeFrame(LEFT);
}

void Player::moveRight()
{
	if (1150 > x) x += playerSpeed;
	changeFrame(RIGHT);
}
