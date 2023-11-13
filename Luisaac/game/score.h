#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <filesystem>

class Score {
public:
	Score(SDL_Renderer* sdl_renderer, int font_size, const SDL_Color &color);
	Score();
	void displayScore() const;

	void loadFont();

	SDL_Texture* getTexture();
	SDL_Rect getRect();
	void addScore(int points);

private:
	SDL_Texture* score_texture = nullptr;
	SDL_Rect rect;
	SDL_Renderer* renderer = nullptr;
	std::string font_path = std::filesystem::current_path().generic_string() + "/game/fonts/arial.ttf";
	int score;
};