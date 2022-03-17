#pragma once

#include <SDL_ttf.h>

struct Level {

	SDL_Color white = { 255, 255, 255 };

	SDL_Rect text_rect;
	SDL_Surface* message;
	SDL_Texture* text;
	std::string levelName;

	void drawLevel();

	Level();
	~Level();
};