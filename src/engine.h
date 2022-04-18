#pragma once
#include <SDL.h>

// feedback: these header and cpp files are a storage for some of the data and don't add any functionality.
// I'd rather suggest to organize this data to proper classes instead.

extern SDL_Window* window;
extern SDL_Renderer* render;

extern bool keys[SDL_NUM_SCANCODES];

extern float delta_time;

extern float playerSpeed;

extern int screenWidth;
extern int screenHeight;