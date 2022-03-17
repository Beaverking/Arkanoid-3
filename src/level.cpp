#include <string>
#include "engine.h"
#include "level.h"
#include "game.h"


void Level::drawLevel()
{
	SDL_SetRenderDrawColor(render, 10, 10, 10, 255);	
	SDL_RenderFillRect(render, &text_rect);

	message = TTF_RenderText_Solid(font, levelName.c_str(), white);
	text = SDL_CreateTextureFromSurface(render, message);
	SDL_RenderCopy(render, text, NULL, &text_rect);

	SDL_FreeSurface(message);
	SDL_DestroyTexture(text);
}

Level::Level()
{
	text_rect = { 0,0,0,0 };
	message = nullptr;
	text = NULL;
}

Level::~Level()
{
	std::cout << "destroy level block " << std::endl;
}
