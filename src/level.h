#pragma once

#include <SDL_ttf.h>

struct Level {

	SDL_Rect text_rect;
	SDL_Surface* message;
	SDL_Texture* text;
	std::string levelName;

	void drawLevel();
};