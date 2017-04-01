#include "ball.h"

void Ball::load()
{
	rect.w = 25;
	rect.h = 25;
	x = 640 / 2;
	y = 480 / 2;
	speed = 0.06f;
	dir = -1;
	ySpeed = 0.02f;
	yDir = -1;
}

void Ball::reset()
{
	x = 640 / 2;
	y = 480 / 2;
	speed = 0.03f;
	dir = -1;
	ySpeed = 0.02f;
	yDir = -1;
}
void Ball::render(SDL_Renderer* renderer, Paddle &lp, Paddle &rp)
{
	if (checkCollision(rect, lp.rect))
	{
		dir = dir * -1;
		yDir = yDir * -1;
		ySpeed = ySpeed * (lp.rect.y / 55);
	}
	if (checkCollision(rect, rp.rect))
	{
		dir = dir * -1;
		yDir = yDir * -1;
		ySpeed = ySpeed * (rp.rect.y / 55);
	}
	if (y < 0)
	{
		yDir = yDir * -1;
	}
	else if (y > 480 - 25)
	{
		yDir = yDir * -1;
	}

	if(x < 0)
	{
		reset();
	}
	else if(x > 640 - 25)
	{
		reset();
	}
	x += speed * dir;
	y += ySpeed * yDir;
	rect.y = (int) y;
	rect.x = (int) x;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}

bool Ball::checkCollision(SDL_Rect A, SDL_Rect B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
