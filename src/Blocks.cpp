#include "Blocks.h"
#include "engine.h"
#include "game.h"


void Block::draw()
{
	SDL_SetRenderDrawColor(render, r, g, b, 255);
	rect.x = x;
	rect.y = y;
	SDL_RenderFillRect(render, &rect);
}

void Block::removeHealth()
{
	if (health <= 3) { 
		hitsToAddBall++;
		health--; 
	}
}

void Block::updateColor()
{
	if (health == 0) {
		r = 0;
		g = 0;
		b = 0;
	}
	if (health == 1) {
		r = 0;
		g = 255;
		b = 0;
	}
	if (health == 2) {
		r = 255;
		g = 228;
		b = 0;
	}
	if (health == 3) {
		r = 255;
		g = 5;
		b = 0;
	}
	if (health == 4) {
		r = 155;
		g = 155;
		b = 155;
	}
}

Block::Block() { rect = { x,y,w,h }; }

Block::~Block()
{
	//std::cout << "Object is being deleted" << std::endl;
}


