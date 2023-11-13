#include "score.h"
#include <iostream>

Score::Score(
	SDL_Renderer* sdl_renderer,
	int font_size, 
	const SDL_Color& color) 
{
	this->renderer = sdl_renderer;
	this->score = 0;
	this->rect = SDL_Rect{ 32, 32, 100, 100 };
}

void Score::displayScore() const {
	SDL_RenderCopy(this->renderer, this->score_texture, nullptr, &rect);
}

void Score::loadFont() {
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), 18);
	if (!font) std::cerr << TTF_GetError() << std::endl;
	auto surface = TTF_RenderText_Solid(font, std::to_string(this->score).c_str(), {255, 255, 255, 255});
	this->score_texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
}

SDL_Texture* Score::getTexture()
{
	return this->score_texture;
}

SDL_Rect Score::getRect()
{
	return this->rect;
}

void Score::addScore(int points)
{
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), 18);
	this->score += points;
	auto surface = TTF_RenderText_Solid(font, std::to_string(this->score).c_str(), { 255, 255, 255, 255 });
	this->score_texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
}