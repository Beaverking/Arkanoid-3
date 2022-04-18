#include "menu.h"
#include "engine.h"
#include "game.h"
#include <SDL_ttf.h>

void MainMenu::DrawMainMenu()
{
	// feedback: would be nice to see more efficient way of drawing. For example TTF_RenderText_Solid are relatively expensive operations
	// as fell as creating textues. They could be done once and result could be saved for further use. Then in draw function you could call
	// the actual rendering sdl functions only. This can be applied for all draw funcitons in your game.

	TitleColor = { color1, 20, color2 };

	titleMessage = TTF_RenderText_Solid(titleFont, "ARKANOID", TitleColor);
	startMessage = TTF_RenderText_Solid(font, "Start", White);
	editorMessage = TTF_RenderText_Solid(font, "Level Editor", White);
	loadMessage = TTF_RenderText_Solid(font, "Load Level", White);
	exitMessage = TTF_RenderText_Solid(font, "Exit Game", White);
	creditsMessage = TTF_RenderText_Solid(creditFont, "Programmed by Niklas Högnabba. 2022 @ FutureGames", White);

	title = SDL_CreateTextureFromSurface(render, titleMessage);
	startText = SDL_CreateTextureFromSurface(render, startMessage);
	editorText = SDL_CreateTextureFromSurface(render, editorMessage);
	loadText = SDL_CreateTextureFromSurface(render, loadMessage);
	exitText = SDL_CreateTextureFromSurface(render, exitMessage);
	creditsText = SDL_CreateTextureFromSurface(render, creditsMessage);

	SDL_SetRenderDrawColor(render, 0, 40, 20, 255);
	
	SDL_RenderFillRect(render, &startTextRect);
	SDL_RenderFillRect(render, &editorTextRect);
	SDL_RenderFillRect(render, &loadTextRect);
	SDL_RenderFillRect(render, &exitTextRect);

	SDL_RenderCopy(render, title, NULL, &titleRect);
	SDL_RenderCopy(render, startText, NULL, &startTextRect);
	SDL_RenderCopy(render, editorText, NULL, &editorTextRect);
	SDL_RenderCopy(render, loadText, NULL, &loadTextRect);
	SDL_RenderCopy(render, exitText, NULL, &exitTextRect);
	SDL_RenderCopy(render, creditsText, NULL, &creditsTextRect);

	// Don't forget to free your surface and texture
	SDL_FreeSurface(titleMessage);
	SDL_FreeSurface(startMessage);
	SDL_FreeSurface(editorMessage);
	SDL_FreeSurface(loadMessage);
	SDL_FreeSurface(exitMessage);
	SDL_FreeSurface(creditsMessage);
	SDL_DestroyTexture(title);
	SDL_DestroyTexture(startText);
	SDL_DestroyTexture(editorText);
	SDL_DestroyTexture(loadText);
	SDL_DestroyTexture(exitText);
	SDL_DestroyTexture(creditsText);
}



void MainMenu::ColorChanger()
{
	// super simple title color changer
	if (!change) {
		color1 += 5;
		color2 -= 3;
		if (color1 >= 240) {
			change = true;
		}
	}
	else {
		color1 -= 5;
		color2 += 3;
		if (color1 <= 10) {
			change = false;
		}
	}
}

MainMenu::MainMenu()
{
	title = nullptr;
	startText = nullptr;
	editorText = nullptr;
	loadText = nullptr;
	exitText = nullptr;
	creditsText = nullptr;
	
	titleRect.x = 100;
	titleRect.y = 80;
	titleRect.w = 800;
	titleRect.h = 100;

	startTextRect.x = 200;
	startTextRect.y = 200;
	startTextRect.w = 400;
	startTextRect.h = 100;

	editorTextRect.x = 200;
	editorTextRect.y = 310;
	editorTextRect.w = 400;
	editorTextRect.h = 100;

	loadTextRect.x = 200;
	loadTextRect.y = 420;
	loadTextRect.w = 400;
	loadTextRect.h = 100;

	exitTextRect.x = 200;
	exitTextRect.y = 530;
	exitTextRect.w = 400;
	exitTextRect.h = 100;
	
	creditsTextRect.x = screenWidth - 505;
	creditsTextRect.y = screenHeight - 45;
	creditsTextRect.w = 500;
	creditsTextRect.h = 40;

	TitleColor = {0, 0, 0 };
	White = { 255, 255, 255 };
	change = false;

	titleMessage = NULL;
	startMessage = NULL;
	editorMessage = NULL;
	loadMessage = NULL;
	exitMessage = NULL;
	creditsMessage = NULL;
}

MainMenu::~MainMenu()
{
}
