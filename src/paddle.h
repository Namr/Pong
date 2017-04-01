#ifndef PADDLE_H
#define PADDLE_H

#include "SDL2/SDL.h"
#include "stdio.h"

class Paddle
{
private:
	int w;
	int h;
	float speed;
	float pos;
public:
	void load(int x);
	void render(SDL_Renderer* renderer,int dir);
	SDL_Rect rect;
};
#endif
