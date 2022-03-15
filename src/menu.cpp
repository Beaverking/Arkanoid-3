
#include <iostream>
#include "menu.h"
#include "engine.h"
#include "game.h"
#include <SDL_ttf.h>

using namespace std;


void MainMenu::DrawMainMenu()
{
	SDL_SetRenderDrawColor(render, 0, 40, 20, 255);
	
	SDL_RenderFillRect(render, &text01_rect);
	SDL_RenderFillRect(render, &text02_rect);
	SDL_RenderFillRect(render, &text03_rect);

	SDL_RenderCopy(render, text01, NULL, &text01_rect);
	SDL_RenderCopy(render, text02, NULL, &text02_rect);
	SDL_RenderCopy(render, text03, NULL, &text03_rect);
	SDL_RenderCopy(render, title, NULL, &title_rect);

	// Don't forget to free your surface and texture
	//SDL_FreeSurface(surfaceMessage);
	//SDL_DestroyTexture(Message);
}

void MainMenu::InitTexts()
{
	White = { 255, 255, 255 };

	startMessage = TTF_RenderText_Solid(font, "Start", White);
	editorMessage = TTF_RenderText_Solid(font, "Level Editor", White);
	loadMessage = TTF_RenderText_Solid(font, "Load Level", White);
	titleMessage = TTF_RenderText_Solid(titleFont, "ARKANOID", White);

	text01 = SDL_CreateTextureFromSurface(render, startMessage);
	text02 = SDL_CreateTextureFromSurface(render, editorMessage);
	text03 = SDL_CreateTextureFromSurface(render, loadMessage);
	title = SDL_CreateTextureFromSurface(render, titleMessage);

	//create a rect
	text01_rect.x = 200;  //controls the rect's x coordinate 
	text01_rect.y = 200; // controls the rect's y coordinte
	text01_rect.w = 400; // controls the width of the rect
	text01_rect.h = 100;

	text02_rect.x = 200;
	text02_rect.y = 310;
	text02_rect.w = 400;
	text02_rect.h = 100;

	text03_rect.x = 200;
	text03_rect.y = 420;
	text03_rect.w = 400;
	text03_rect.h = 100;

	title_rect.x = 100;
	title_rect.y = 80;
	title_rect.w = 800;
	title_rect.h = 100;

	text01 = SDL_CreateTextureFromSurface(render, startMessage);
	text02 = SDL_CreateTextureFromSurface(render, editorMessage);
	title = SDL_CreateTextureFromSurface(render, titleMessage);
}



MainMenu::MainMenu()
{
}
