#include "engine.h"

SDL_Window* window;
SDL_Renderer* render;

bool keys[SDL_NUM_SCANCODES] = { false };

float delta_time = 0.f;

float playerSpeed = 420.69f;

int screenWidth = 1280;
int screenHeight = 720;
