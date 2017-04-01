#ifndef BALL_H_
#define BALL_H_

#include "SDL2/SDL.h"
#include "paddle.h"
class Ball
{
private:
	float x;
	float y;
	float speed;
	int dir;
	bool checkCollision( SDL_Rect A, SDL_Rect B);
public:
	void load();
	void render(SDL_Renderer* renderer,Paddle &lp,Paddle &rp);
	SDL_Rect rect;
};

#endif /* BALL_H_ */
