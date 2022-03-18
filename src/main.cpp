#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "engine.h"
#include "game.h"

using namespace std;

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    //SDL_Init(SDL_INIT_AUDIO);
    window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, 0);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;

    atStart = true;

    Uint64 prevTicks = SDL_GetPerformanceCounter();
    
    LoadAudioFiles();
    LoadFont();
    
    currentMenu = Menu::mainMenu;

    while (running) 
    {
        Uint64 ticks = SDL_GetPerformanceCounter();
        Uint64 delta_ticks = ticks - prevTicks;
        prevTicks = ticks;
        //printf("delta_ticks = %lld\n", delta_ticks);

        delta_time = (float)delta_ticks / SDL_GetPerformanceFrequency();
        //printf("delta_time = %f\n", delta_time);
        //printf("FPS %f\n", 1.f / delta_time);

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_TEXTINPUT: {
                levelEditor.saveBoxString += event.text.text;                
                break; }

            case SDL_KEYDOWN: {
                int scancode = event.key.keysym.scancode;

                if (scancode == SDL_SCANCODE_ESCAPE) {
                    if (currentMenu == Menu::mainMenu) {
                        running = false;
                    }
                    else {
                        currentMenu = Menu::mainMenu;
                    }
                }

                keys[scancode] = true;

                if (currentMenu == Menu::saveAs) {
                    if (scancode == SDL_SCANCODE_BACKSPACE && levelEditor.saveBoxString.length() > 0)                    {
                        levelEditor.saveBoxString.pop_back();
                    }
                    
                    if (scancode == SDL_SCANCODE_RETURN && levelEditor.saveBoxString.length() > 0) {
                        levelEditor.SaveLevel(levelEditor.saveBoxString);
                        SDL_StopTextInput();
                        ConstructLevel(levelEditor.saveBoxString);
                        currentMenu = Menu::game;
                    }
                }

                break; }

            case SDL_KEYUP: {
                int scancode = event.key.keysym.scancode;
                keys[scancode] = false;

                break; }

            case SDL_MOUSEBUTTONUP: {
                int x = event.button.x;
                int y = event.button.y;

                if (currentMenu == Menu::mainMenu) {
                    if (InsideRect(mainMenu.startTextRect, x, y))
                    {
                        string level1 = "level1";
                        ConstructLevel(level1);
                        currentMenu = Menu::game;
                    }
                    if (InsideRect(mainMenu.editorTextRect, x, y))
                    {
                        levelEditor.ConstructLevelEditorBlocks();
                        currentMenu = Menu::levelEditor;
                    }
                    if (InsideRect(mainMenu.loadTextRect, x, y))
                    {
                        LoadLevels();
                        currentMenu = Menu::loadLevel;
                    }
                    if (InsideRect(mainMenu.exitTextRect, x, y))
                    {
                        running = false;
                    }
                }               

                if (currentMenu == Menu::levelEditor) {
                    for (size_t i = 0; i < levelEditor.editor_blocks.size(); i++)
                    {   
                        if (InsideRect(levelEditor.editor_blocks[i].rect, x, y))                        
                        {
                            levelEditor.editor_blocks[i].health++;
                            levelEditor.editor_blocks[i].health = levelEditor.editor_blocks[i].health % 5;
                            levelEditor.editor_blocks[i].updateColor();
                            break;
                        }
                    }

                    if (InsideRect(levelEditor.button1, x, y))
                    {                       
                        SDL_StartTextInput();
                        levelEditor.saveBoxString = "";
                        currentMenu = Menu::saveAs;
                    }
                }

                if (currentMenu == Menu::loadLevel) {
                    for (size_t i = 0; i < levels.size(); i++)
                    {
                        if (InsideRect(levels[i].text_rect, x, y))
                        {
                            cout << levels[i].levelName << endl;
                            ConstructLevel(levels[i].levelName);
                            currentMenu = Menu::game;
                            break;
                        }
                    }
                }
                break; }
            }
		}

		if (currentMenu != Menu::mainMenu) {
			SDL_SetRenderDrawColor(render, 25, 25, 150, 255);
			SDL_RenderClear(render);
		}

		if (currentMenu == Menu::mainMenu) {
            mainMenu.ColorChanger();
			SDL_SetRenderDrawColor(render, mainMenu.color2, 25, mainMenu.color1, 255);
			SDL_RenderClear(render);
			mainMenu.DrawMainMenu();
        }
        else if(currentMenu == Menu::saveAs) {
            levelEditor.DrawSaveBox();
        }
        else if (currentMenu == Menu::levelEditor) {
            for (size_t i = 0; i < levelEditor.editor_blocks.size(); i++)
            {
                levelEditor.editor_blocks[i].draw();
            }
            levelEditor.DrawLevelEditor();
        }
        else if (currentMenu == Menu::loadLevel) {
            for (size_t i = 0; i < levels.size(); i++)
            {
                levels[i].drawLevel();
            }
        }
        else if (currentMenu == Menu::game) {
            player.draw();
            player.update();

            HitsToNewBall();

            //Balls
            for (auto& ball : balls) {
                if (!ball.alive) {
                    continue;
                }

                if (atStart) {
                    ball.ballInStart(player.rect);
                }
                else {
                    ball.move();
                    ball.checkCollisionPlayer(player.rect);
                    ball.checkCollisionEdge();
                }
                ball.draw();
            }

            bool end = true;

            //blocks
            for (size_t i = 0; i < blocks.size(); i++)
            {
                if (blocks[i].health > 0) {

                    if (blocks[i].health == 4) end = true;
                    else end = false;

                    blocks[i].draw();
                    for (auto& ball : balls) {

                        if (!ball.alive) {
                            continue;
                        }

                        if (ball.checkCollisionBlock(&blocks[i])) {
                            ball.collidedBlocksIndex.push_back(i);
                        }
                    }
                }                
            }

            if (end) currentMenu = Menu::mainMenu;
            end = true;

            for (auto& ball : balls) {
                ball.collision();
                if (ball.alive) end = false;
            }

            if (end) currentMenu = Menu::mainMenu;
        }

		SDL_RenderPresent(render);

		SDL_Delay(16);
	}

    //Mix_FreeChunk(beep);

    Mix_CloseAudio();
    SDL_Quit();
}