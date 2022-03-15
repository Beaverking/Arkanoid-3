#pragma once

#include "Blocks.h"
#include <SDL_ttf.h>

struct LevelEditor {
	void DrawLevelEditor();
	void InitTexts();
	void SaveLevel(std::string saveText);
	void DrawSaveBox();

	std::string saveBoxString;
	

	std::vector<Block> editor_blocks;

	SDL_Texture* text0;
	SDL_Texture* text1;
	SDL_Texture* text2;
	SDL_Texture* text3;
	SDL_Texture* text4;
	SDL_Texture* text5;
	SDL_Texture* text6;
	SDL_Texture* text7;
	SDL_Texture* text8;
	SDL_Texture* text9;
	SDL_Texture* savetext;

	SDL_Rect text0_rect;
	SDL_Rect text1_rect;
	SDL_Rect text2_rect;
	SDL_Rect text3_rect;
	SDL_Rect text4_rect;
	SDL_Rect text5_rect;
	SDL_Rect text6_rect;
	SDL_Rect text7_rect;
	SDL_Rect text8_rect;
	SDL_Rect text9_rect;
	SDL_Rect save_rect;

	SDL_Surface* message0;
	SDL_Surface* message1;
	SDL_Surface* message2;
	SDL_Surface* message3;
	SDL_Surface* message4;
	SDL_Surface* message5;
	SDL_Surface* message6;
	SDL_Surface* message7;
	SDL_Surface* message8;
	SDL_Surface* message9;
	SDL_Surface* saveMessage;

	SDL_Rect button1;

	LevelEditor();
	~LevelEditor();
};
