#include "paddle.h"

void Paddle::load(int x)
{
	w = 30;
	h = 100;
	rect.x = x;
	rect.y = 30;
	rect.h = h;
	rect.w = w;
	speed = 0.03f;
	pos = rect.y;
}

void Paddle::render(SDL_Renderer* renderer,int dir)
{
	//paddle movement logic
	if(pos > 0)
	{
		if(pos < 480 - 100)
		{
			pos += speed * dir;
		}
		else
		{
			pos -= 1;
		}
	}
	else
	{
		pos += 1;
	}
	rect.y = (int) pos;
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderFillRect( renderer, &rect);
}
