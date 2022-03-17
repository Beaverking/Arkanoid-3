#pragma once

#include <SDL.h>
#include "Blocks.h"

//The dot that will move around on the screen
class Ball
{
public:
    //The dimensions of the dot
    static const int BALL_WIDTH = 20;
    static const int BALL_HEIGHT = 20;

    //Maximum axis velocity of the dot
    static const int DOT_VEL = 10;

    //Initializes the variables
    Ball();
    ~Ball();

    
    //Moves the dot and checks collision
    void move();

    //Shows the dot on the screen
    void draw();

    void ballInStart(const SDL_Rect& player);

    void checkCollisionPlayer(const SDL_Rect& object);

    bool checkCollisionBlock(Block* object);

    void checkCollisionEdge();

    void collision();

    std::vector<int> collidedBlocksIndex;

    int id;
    bool alive;


private:
    //The X and Y offsets of the dot
    int posX, posY;

    //The velocity of the dot
    int velX, velY;

    int curVelX, curVelY;

    bool moveRight = true;
    bool moveDown = true;

    //Dot's collision box
    SDL_Rect ballCollider;
};