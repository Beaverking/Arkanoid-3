#pragma once

#include <SDL.h>

class Block
{
	
public:
	//Color
	int r = 0;
	int g = 0;
	int b = 0;
	int a = 255;

	SDL_Rect rect;

	void draw();

	void removeHealth();
	void updateColor();

	Block();


	int x = 0;
	int y = 0;

	int w = 70;
	int h = 16;

	int health = 1;
};