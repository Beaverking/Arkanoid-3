#pragma once

#include "Blocks.h"
#include <SDL_ttf.h>

struct LevelEditor {
	void DrawLevelEditor();
	void SaveLevel(std::string saveText);
	void DrawSaveBox();
	void ConstructLevelEditorBlocks();

	std::string saveBoxString;

	SDL_Color white = { 255, 255, 255 };
	SDL_Color change = { 0, 255, 0 };	

	std::vector<Block> editor_blocks;
		
	SDL_Texture* textTextures[10];
	SDL_Rect textRects[10];
	SDL_Surface* surfaceMessages[10];
	
	SDL_Texture* savetext;
	SDL_Rect save_rect;	
	SDL_Surface* saveMessage;
	SDL_Rect button1;

	LevelEditor();
	~LevelEditor();
};
