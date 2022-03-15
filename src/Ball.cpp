#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "engine.h"
#include "game.h"

using namespace std;

Ball::Ball()
{
    //Initialize the offsets
    mPosX = 300;
    mPosY = 640;

    //Set collision box dimension
    mCollider.w = BALL_WIDTH;
    mCollider.h = BALL_HEIGHT;

    //Initialize the velocity
    mVelX = 300;
    mVelY = 300;

    curVelX = 300;
    curVelY = 300;

    //std::vector<Block> &collidedBlocks;
}

void Ball::update()
{
}

void Ball::move()
{   
    mVelX = delta_time * curVelX;
    mVelY = delta_time * curVelY;

    //Move the ball left or right

    if (moveRight) { mPosX += mVelX; }
    else { mPosX -= mVelX; }    
    mCollider.x = mPosX;

    //If the ball collided with right/left edge
    if (mPosX + BALL_WIDTH > screenWidth) { 
        moveRight = false; 
        PlayBeep();
    }
    if (mPosX < 0) { 
        moveRight = true;
        PlayBeep();
    }

    //Move the ball up or down
    if (moveDown) { mPosY += mVelY; }
    else { mPosY -= mVelY; }
    mCollider.y = mPosY;

    //If the ball collided with top/down edge
    if ((mPosY + BALL_HEIGHT > screenHeight)) { 
        moveDown = false; 
        PlayBeep();
    }
    if (mPosY < 0) { 
        moveDown = true; 
        PlayBeep();
    }    
}

void Ball::draw()
{
    SDL_SetRenderDrawColor(render, 0, 40, 20, 255);
    SDL_Rect ball = { mPosX, mPosY, BALL_WIDTH, BALL_WIDTH };
    SDL_RenderFillRect(render, &ball);
}

void Ball::ballInStart(const SDL_Rect& player){   
    mPosX = player.x + (player.w / 2);
    mPosY = player.y - 10;
}

void Ball::checkCollisionPlayer(const SDL_Rect& player){

	//Calculate the sides of rect object
	int object_left = player.x;
    int object_right = player.x + player.w;
	int object_top = player.y;
    int object_bottom = player.y + player.h;

    int ball_left = mPosX;
    int ball_right = mPosX + BALL_WIDTH;
    int ball_top = mPosY;
    int ball_bottom = mPosY + BALL_WIDTH;

    int ball_middle = (mPosX + (BALL_WIDTH / 2));

    int b_collision = object_bottom - mPosY;
    int t_collision = ball_bottom - player.y;
    int l_collision = ball_right - player.x;
    int r_collision = object_right - mPosX;

    if (ball_bottom >= object_top)
    {
        if (ball_top <= object_bottom)
        {
            if (ball_right >= object_left)
            {
                if (ball_left <= object_right)
                {                      
                    PlayBeep();

                    if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision)
                    {
                        cout << "Paddle top collision" << endl;
                        moveDown = false;

                        if (ball_middle < object_left + (player.w / 6)) {
                            curVelX = 400;
                            curVelY = 200;
                            moveRight = false;
                        }
                        else if (ball_middle < object_left + (player.w / 3)) {
                            curVelX = 300;
                            curVelY = 300;
                            moveRight = false;
                        }
                        else if (ball_middle < object_left + (player.w / 2)) {
                            curVelX = 200;
                            curVelY = 400;
                            moveRight = false;
                        }
                        else if (ball_middle < object_left + (player.w / 3) * 2) {
                            curVelX = 200;
                            curVelY = 400;
                            moveRight = true;
                        }
                        else if (ball_middle < object_left + (player.w / 6) * 5) {
                            curVelX = 300;
                            curVelY = 300;
                            moveRight = true;
                        }
                        else{
                            curVelX = 400;
                            curVelY = 200;
                            moveRight = true;
                        }
                    }

                    if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
                    {
                        cout << "Paddle bottom collision" << endl;
                        moveDown = true;
                    }
                    if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
                    {
                        cout << "Paddle left collision" << endl;
                        moveRight = false;
                    }
                    if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
                    {
                        cout << "Paddle right collision" << endl;
                        moveRight = true;
                    }
                }
            }
        }
    }
}

bool Ball::checkCollisionBlock(Block* object){

    //Calculate the sides of rect object
    int object_left = object->x;
    int object_right = object->x + object->w;
    int object_top = object->y;
    int object_bottom = object->y + object->h;

    int ball_left = mPosX;
    int ball_right = mPosX + BALL_WIDTH;
    int ball_top = mPosY;
    int ball_bottom = mPosY + BALL_WIDTH;

    int b_collision = object_bottom - mPosY;
    int t_collision = ball_bottom - object->y;
    int l_collision = ball_right - object->x;
    int r_collision = object_right - mPosX;

	if (ball_bottom > object_top)
	{
		if (ball_top < object_bottom)
		{
			if (ball_right > object_left)
			{
				if (ball_left < object_right)
				{					
                    //object->health = object->health - 1;  
                    //cout << object->health << endl;
                    PlayBeep();
                    
                    //collidedBlocks.push_back(*object);
                    
					/*if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision)
					{
						cout << "top collision" << endl;
						moveDown = false;
					}
					if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
					{
						cout << "bottom collision" << endl;
						moveDown = true;
					}
					if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
					{
						cout << "left collision" << endl;
						moveRight = false;
					}
					if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
					{
						cout << "Right collision" << endl;
						moveRight = true;
					}*/

                    return true;
				}
			}
		}
	}
    return false;
}

void Ball::collision()
{
    if (collidedBlocksIndex.size() == 0) return;

    int index = -1;
    int closest = 200;

    cout << "total collided blocks: " << collidedBlocksIndex.size() << endl;

    for (size_t i = 0; i < collidedBlocksIndex.size(); i++)
    {
        int tempX = blocks[collidedBlocksIndex[i]].x + blocks[collidedBlocksIndex[i]].w / 2;
        tempX -= mPosX + BALL_WIDTH / 2;
        int tempY = blocks[collidedBlocksIndex[i]].y + blocks[collidedBlocksIndex[i]].h / 2;
        tempY -= mPosY + BALL_WIDTH / 2;

        tempX = abs(tempX);
        tempY = abs(tempY);
        std::cout << "block index : " << collidedBlocksIndex[i] << std::endl;
        std::cout << "block temp X : " << tempX << "block temp Y : " << tempY << std::endl;
        tempX += tempY;

        if (tempX < closest) {
            closest = tempX;
            index = collidedBlocksIndex[i];
        }
    }

    int b_collision = (blocks[index].y + blocks[index].h) - mPosY;
    int t_collision = (mPosY + BALL_WIDTH) - blocks[index].y;
    int l_collision = (mPosX + BALL_WIDTH) - blocks[index].x;
    int r_collision = (blocks[index].x + blocks[index].w) - mPosX;


    if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision)
    {
        cout << "top collision" << endl;
        moveDown = false;
    }
    if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
    {
        cout << "bottom collision" << endl;
        moveDown = true;
    }
    if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
    {
        cout << "left collision" << endl;
        moveRight = false;
    }
    if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
    {
        cout << "Right collision" << endl;
        moveRight = true;
    }


    blocks[index].removeHealth();
    blocks[index].updateColor();
    collidedBlocksIndex.clear();

}


