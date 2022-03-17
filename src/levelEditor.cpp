#include <iostream>
#include <vector>
#include <fstream>

#include "levelEditor.h"
#include "Blocks.h"
#include "engine.h"
#include "game.h"

void LevelEditor::DrawLevelEditor()
{  
    change = { 0, 255, 0 };
    surfaceMessages[0] = TTF_RenderText_Solid(font, "Green   ", change);
    surfaceMessages[1] = TTF_RenderText_Solid(font, "1 hp    ", white);
    change = { 255, 228, 0 };
    surfaceMessages[2] = TTF_RenderText_Solid(font, "Yellow  ", change);
    surfaceMessages[3] = TTF_RenderText_Solid(font, "2 hp    ", white);
    change = { 255, 5, 0 };
    surfaceMessages[4] = TTF_RenderText_Solid(font, "Red     ", change);
    surfaceMessages[5] = TTF_RenderText_Solid(font, "3 hp    ", white);
    change = { 155, 155, 155 };
    surfaceMessages[6] = TTF_RenderText_Solid(font, "Gray    ", change);
    surfaceMessages[7] = TTF_RenderText_Solid(font, "stone   ", white);
    change = { 0, 0, 0 };
    surfaceMessages[8] = TTF_RenderText_Solid(font, "Black   ", change);
    surfaceMessages[9] = TTF_RenderText_Solid(font, "no block", white);

    for (unsigned int i = 0; i < 10; i++)
    {
        textTextures[i] = SDL_CreateTextureFromSurface(render, surfaceMessages[i]);
        SDL_RenderCopy(render, textTextures[i], NULL, &textRects[i]);
        SDL_FreeSurface(surfaceMessages[i]);
        SDL_DestroyTexture(textTextures[i]);
    }

    SDL_SetRenderDrawColor(render, 200, 24, 100, 255);
    button1 = { screenWidth - 40, screenHeight - 30, 30, 20 };
    SDL_RenderFillRect(render, &button1);

    saveMessage = TTF_RenderText_Solid(font, "Save as", white);
    savetext = SDL_CreateTextureFromSurface(render, saveMessage);
    SDL_RenderCopy(render, savetext, NULL, &save_rect);
    SDL_FreeSurface(saveMessage);
    SDL_DestroyTexture(savetext);
}

void LevelEditor::SaveLevel(std::string saveText)
{
    std::string editorLevel;
    for (unsigned int i = 0; i < 256; i++)
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

    SDL_Surface* titleMessage = TTF_RenderText_Solid(font, "save level as", { 255, 255, 255 });
    SDL_Texture* titleBox = SDL_CreateTextureFromSurface(render, titleMessage);
    SDL_RenderCopy(render, titleBox, NULL, &titleRect);

    int textLenght = (int)saveBoxString.length();

    SDL_Rect saveBoxRect = { 500, 500, 12 * textLenght, 50};
    SDL_SetRenderDrawColor(render, 100, 10, 150, 255);
    SDL_RenderFillRect(render, &saveBoxRect);

    SDL_Surface* saveBoxMessage = TTF_RenderText_Solid(font, saveBoxString.c_str(), {255, 255, 255});
    SDL_Texture* saveBox = SDL_CreateTextureFromSurface(render, saveBoxMessage);
    SDL_RenderCopy(render, saveBox, NULL, &saveBoxRect);

    // Don't forget to free your surface and texture
    SDL_FreeSurface(saveBoxMessage);
    SDL_DestroyTexture(saveBox);
    SDL_FreeSurface(titleMessage);
    SDL_DestroyTexture(titleBox);
}

void LevelEditor::ConstructLevelEditorBlocks()
{
    editor_blocks.clear();
    editor_blocks.reserve(256);

    for (unsigned int i = 0; i < 256; i++)
    {
        Block block;

        block.x = i % 16 * (block.w + 10);
        block.y = i / 16 * (block.h + 10);

        block.health = 1;

        block.updateColor();

        editor_blocks.push_back(block);
    }
}

LevelEditor::LevelEditor()
{   
    for (unsigned int i = 0; i < 10; i++)
    {
        if (i % 2 == 0) {
            textRects[i].x = 10;
            textRects[i].y = screenHeight - 250 + (i * 25);
            textRects[i].w = 80;
            textRects[i].h = 40;
        }
        else {
            textRects[i].x = 90;
            textRects[i].y = textRects[i - 1].y;
            textRects[i].w = 80;
            textRects[i].h = 40;
        }
    }

    button1.x = 200;
    button1.y = 210;
    button1.w = 400;
    button1.h = 100;

    saveMessage = NULL;
    savetext = nullptr;

    save_rect.x = screenWidth - 140;
    save_rect.y = screenHeight - 40;
    save_rect.w = 80;
    save_rect.h = 40;
}

LevelEditor::~LevelEditor()
{
}


