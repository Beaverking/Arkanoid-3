#include "player.h"
#include "engine.h"
#include "game.h"

void Player::draw() {
	SDL_SetRenderDrawColor(render, 200, 40, 20, 255);
	//rect = {x,y,w,h};
	rect.x = x;
	rect.y = y;
	SDL_RenderFillRect(render, &rect);
}

void Player::update() {
	if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
		if (x + w < screenWidth) x += playerSpeed * delta_time;
	}	
	if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
		if (x > 0) x -= playerSpeed * delta_time;
	}
	if (keys[SDL_SCANCODE_SPACE]) {
		atStart = false;
	}
}

Player::Player(){ rect = { x,y,w,h }; }