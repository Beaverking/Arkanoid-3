#include <iostream>
#include <vector>
#include <fstream>

#include "levelEditor.h"
#include "Blocks.h"
#include "engine.h"
#include "game.h"

void LevelEditor::DrawLevelEditor()
{
    SDL_SetRenderDrawColor(render, 200, 24, 100, 255);
    button1 = { screenWidth - 40, screenHeight - 30, 30, 20 };
    SDL_RenderFillRect(render, &button1);

    SDL_RenderCopy(render, text0, NULL, &text0_rect);
    SDL_RenderCopy(render, text1, NULL, &text1_rect);
    SDL_RenderCopy(render, text2, NULL, &text2_rect);
    SDL_RenderCopy(render, text3, NULL, &text3_rect);
    SDL_RenderCopy(render, text4, NULL, &text4_rect);
    SDL_RenderCopy(render, text5, NULL, &text5_rect);
    SDL_RenderCopy(render, text6, NULL, &text6_rect);
    SDL_RenderCopy(render, text7, NULL, &text7_rect);
    SDL_RenderCopy(render, text8, NULL, &text8_rect);
    SDL_RenderCopy(render, text9, NULL, &text9_rect);
    SDL_RenderCopy(render, savetext, NULL, &save_rect);
}

void LevelEditor::InitTexts()
{
    std::cout << "create level editor texts" << std::endl;

    SDL_Color white = { 255, 255, 255 };
    SDL_Color change = { 0, 255, 0 };

    message0 = TTF_RenderText_Solid(font, "Green   ", change);
    message1 = TTF_RenderText_Solid(font, "1 hp    ", white);
    change = { 255, 228, 0 };
    message2 = TTF_RenderText_Solid(font, "Yellow  ", change);
    message3 = TTF_RenderText_Solid(font, "2 hp    ", white);
    change = { 255, 5, 0 };
    message4 = TTF_RenderText_Solid(font, "Red     ", change);
    message5 = TTF_RenderText_Solid(font, "3 hp    ", white);
    change = { 155, 155, 155 };
    message6 = TTF_RenderText_Solid(font, "Gray    ", change);
    message7 = TTF_RenderText_Solid(font, "stone   ", white);
    change = { 0, 0, 0 };
    message8 = TTF_RenderText_Solid(font, "Black   ", change);
    message9 = TTF_RenderText_Solid(font, "no block", white);
    saveMessage = TTF_RenderText_Solid(font, "Save as", white);

    text0 = SDL_CreateTextureFromSurface(render, message0);
    text1 = SDL_CreateTextureFromSurface(render, message1);
    text2 = SDL_CreateTextureFromSurface(render, message2);
    text3 = SDL_CreateTextureFromSurface(render, message3);
    text4 = SDL_CreateTextureFromSurface(render, message4);
    text5 = SDL_CreateTextureFromSurface(render, message5);
    text6 = SDL_CreateTextureFromSurface(render, message6);
    text7 = SDL_CreateTextureFromSurface(render, message7);
    text8 = SDL_CreateTextureFromSurface(render, message8);
    text9 = SDL_CreateTextureFromSurface(render, message9);
    savetext = SDL_CreateTextureFromSurface(render, saveMessage);

    text0_rect.x = 10;
    text0_rect.y = screenHeight - 250;
    text0_rect.w = 80;
    text0_rect.h = 40;

    text1_rect.x = 90;
    text1_rect.y = screenHeight - 250;
    text1_rect.w = 80;
    text1_rect.h = 40;

    text2_rect.x = 10;
    text2_rect.y = screenHeight - 200;
    text2_rect.w = 80;
    text2_rect.h = 40;

    text3_rect.x = 90;
    text3_rect.y = screenHeight - 200;
    text3_rect.w = 80;
    text3_rect.h = 40;

    text4_rect.x = 10;
    text4_rect.y = screenHeight - 150;
    text4_rect.w = 80;
    text4_rect.h = 40;

    text5_rect.x = 90;
    text5_rect.y = screenHeight - 150;
    text5_rect.w = 80;
    text5_rect.h = 40;

    text6_rect.x = 10;
    text6_rect.y = screenHeight - 100;
    text6_rect.w = 80;
    text6_rect.h = 40;

    text7_rect.x = 90;
    text7_rect.y = screenHeight - 100;
    text7_rect.w = 80;
    text7_rect.h = 40;

    text8_rect.x = 10;
    text8_rect.y = screenHeight - 50;
    text8_rect.w = 80;
    text8_rect.h = 40;

    text9_rect.x = 90;
    text9_rect.y = screenHeight - 50;
    text9_rect.w = 80;
    text9_rect.h = 40;

    save_rect.x = screenWidth - 140;
    save_rect.y = screenHeight - 40;
    save_rect.w = 80;
    save_rect.h = 40;
}

void LevelEditor::SaveLevel(std::string saveText)
{
    std::string editorLevel;
    for (size_t i = 0; i < 256; i++)
    {        
        char c = '0' + editor_blocks[i].health;
        editorLevel.push_back(c);
    }

    std::string levelname = "levels/" + saveText + ".txt";
    std::ofstream myfile;
    myfile.open(levelname, std::ofstream::out | std::ofstream::trunc);
    myfile << editorLevel;
    myfile.close();
    
}

void LevelEditor::DrawSaveBox()
{
    SDL_Rect titleRect = { 500, 300, 200, 50 };

    SDL_Surface* titleMessage = TTF_RenderText_Solid(font, "save level as:", { 255, 255, 255 });
    SDL_Texture* titleBox = SDL_CreateTextureFromSurface(render, titleMessage);
    SDL_RenderCopy(render, titleBox, NULL, &titleRect);


    int textLenght = saveBoxString.length();

    SDL_Rect saveBoxRect = { 500, 500, 12 * textLenght, 50};
    SDL_SetRenderDrawColor(render, 100, 10, 150, 255);
    SDL_RenderFillRect(render, &saveBoxRect);

    SDL_Surface* saveBoxMessage = TTF_RenderText_Solid(font, saveBoxString.c_str(), {255, 255, 255});
    SDL_Texture* saveBox = SDL_CreateTextureFromSurface(render, saveBoxMessage);
    SDL_RenderCopy(render, saveBox, NULL, &saveBoxRect);
}

LevelEditor::LevelEditor()
{   
    for (size_t i = 0; i < 256; i++)
    {
        Block block;

        block.x = i % 16 * (block.w + 10);
        block.y = i / 16 * (block.h + 10);

        block.health = 1;

        block.updateColor();

        editor_blocks.push_back(block);
    }
    
    button1.x = 200;  //controls the rect's x coordinate 
    button1.y = 210; // controls the rect's y coordinte
    button1.w = 400; // controls the width of the rect
    button1.h = 100;
}

LevelEditor::~LevelEditor()
{
    editor_blocks.clear();
    SDL_FreeSurface(message0);
    SDL_DestroyTexture(text0);
}


