#pragma once
#include "pause.h"

class DeathScreen : public Pause
{
public:
	void initialize(SDL_Renderer* renderer);
};