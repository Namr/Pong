#include <SDL2/SDL.h>
#include <stdio.h>

#include "paddle.h"
#include "ball.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* Window = NULL;

SDL_Renderer* Renderer = NULL;

Paddle Lpaddle;
Paddle Rpaddle;
Ball ball;

int Ldir;
int Rdir;

float Bx = SCREEN_WIDTH / 2;
float By = SCREEN_HEIGHT / 2;


double deltaTime = 0;

bool init();

bool load();

void render();

void close();

int main(int argc, char* args[])
{

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!load())
		{
			printf("Failed to load media!\n");
		}
		else
		{

			bool quit = false;

			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					switch (e.type)
					{

					case SDL_QUIT:
						quit = true;
						break;
					case SDL_KEYDOWN:
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							Rdir = -1;
							break;
						case SDLK_DOWN:
							Rdir = 1;
							break;
						case SDLK_w:
							Ldir = -1;
							break;
						case SDLK_s:
							Ldir = 1;
							break;
						}
						break;

					case SDL_KEYUP:
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							if (Rdir < 0)
								Rdir = 0;
							break;
						case SDLK_DOWN:
							if (Rdir > 0)
								Rdir = 0;
							break;
						case SDLK_w:
							if (Ldir < 0)
								Ldir = 0;
							break;
						case SDLK_s:
							if (Ldir > 0)
								Ldir = 0;
							break;
						}
						break;
					}
				}
				LAST = NOW;
				NOW = SDL_GetPerformanceCounter();

				deltaTime = (double) ((NOW - LAST) * 1000
						/ SDL_GetPerformanceFrequency());

				render();

				SDL_RenderPresent(Renderer);
			}
		}
	}
	close();

	return 0;
}

void render()
{
	//clear screen
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);

	Lpaddle.render(Renderer,Ldir);
	Rpaddle.render(Renderer,Rdir);
	ball.render(Renderer,Lpaddle,Rpaddle);
}

bool init()
{
	bool success = true;

	if (SDL_Init( SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		Window = SDL_CreateWindow("Pong",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (Window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n",
					SDL_GetError());
			success = false;
		}
		else
		{
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
		}
	}

	return success;
}

bool load()
{
	bool success = true;
	Lpaddle.load(30);
	Rpaddle.load(580);
	ball.load();
	return success;
}

void close()
{
	SDL_DestroyWindow(Window);
	Window = NULL;

	SDL_Quit();
}
