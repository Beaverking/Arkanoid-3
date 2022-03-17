#pragma once

#include <SDL_ttf.h>

struct MainMenu {
	void DrawMainMenu();
	void ColorChanger();
	
	SDL_Color White;
	SDL_Color TitleColor;

	Uint8 color1 = 0;
	Uint8 color2 = 255;
	bool change;

	SDL_Rect titleRect;
	SDL_Rect startTextRect;
	SDL_Rect editorTextRect;
	SDL_Rect loadTextRect;
	SDL_Rect exitTextRect;
	SDL_Rect creditsTextRect;

	SDL_Texture* title;
	SDL_Texture* startText;
	SDL_Texture* editorText;
	SDL_Texture* loadText;
	SDL_Texture* exitText;
	SDL_Texture* creditsText;

	SDL_Surface* titleMessage;
	SDL_Surface* startMessage;
	SDL_Surface* editorMessage;
	SDL_Surface* loadMessage;
	SDL_Surface* exitMessage;
	SDL_Surface* creditsMessage;

	MainMenu();
	~MainMenu();
};





