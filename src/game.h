#pragma once

#include <vector>
#include <list>
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


extern Player player;
extern MainMenu mainMenu;
extern LevelEditor levelEditor;
extern std::vector<Block> blocks;
extern std::list<Ball> balls;

extern void ConstructLevel(std::string level);
extern void LoadAudio();
void LoadFont();
void LoadLevels();
void AddBall();
extern void HitsToNewBall();
bool InsideRect(SDL_Rect rect, int mouseX, int mouseY);

extern TTF_Font* titleFont;
extern TTF_Font* font;
extern TTF_Font* creditFont;

extern bool atStart;
extern int hitsToAddBall;
extern int ballID;

extern enum class Menu {
	mainMenu, levelEditor, loadLevel, saveAs, game
};

extern Menu currentMenu;

extern std::vector<Level> levels;


