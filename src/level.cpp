#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "engine.h"
#include "level.h"
#include "game.h"


void Level::drawLevel()
{
	SDL_SetRenderDrawColor(render, 10, 10, 10, 255);	
	SDL_RenderFillRect(render, &text_rect);
	SDL_RenderCopy(render, text, NULL, &text_rect);
}
