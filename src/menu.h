#pragma once

#include <SDL_ttf.h>

struct MainMenu {
	void DrawMainMenu();
	void InitTexts();
	
	SDL_Color White;
	SDL_Color TitleColor;

	Uint8 red = 0;
	bool change;

	SDL_Rect text01_rect;
	SDL_Rect text02_rect;
	SDL_Rect text03_rect;
	SDL_Rect title_rect;
	SDL_Texture* text01;
	SDL_Texture* text02;
	SDL_Texture* text03;
	SDL_Texture* title;
	SDL_Surface* startMessage;
	SDL_Surface* editorMessage;
	SDL_Surface* titleMessage;
	SDL_Surface* loadMessage;


	MainMenu();
};





