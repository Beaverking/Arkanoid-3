#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <SDL_ttf.h>

#include <filesystem>

#include "Ball.h"
#include "engine.h"
#include "player.h"
#include "Blocks.h"
#include "audio.h"
#include "menu.h"
#include "levelEditor.h"
#include "level.h"


extern Ball ball;
extern Player player;
extern MainMenu mainMenu;
extern LevelEditor levelEditor;
extern std::vector<Block> blocks;

extern void ConstructLevel(std::string level);
extern void LoadAudio();
void LoadFont();
void LoadLevels();
extern TTF_Font* titleFont;
extern TTF_Font* font;

extern bool atStart;

extern enum class Menu {
	mainMenu, levelEditor, loadLevel, saveAs, game
};


extern std::vector<int> collidedBlocksIndex;

extern std::vector<Level> levels;


