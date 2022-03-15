#pragma once

#include <SDL.h>

struct Player {

	//Initialize the offsets
	int x = 640;
	int y = 680;

	int w = 128;
	int h = 32;

	SDL_Rect rect;


	void update();
	void draw();

	Player();
};
