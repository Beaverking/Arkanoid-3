#pragma once
#include <SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* render;

extern bool keys[SDL_NUM_SCANCODES];

extern float delta_time;

extern float playerSpeed;

extern int screenWidth;
extern int screenHeight;