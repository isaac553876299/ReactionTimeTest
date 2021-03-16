#include <iostream>
#include "SDL.h"
#include <time.h>

int main(int argc, char** argv)
{
	bool active(true);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	srand(time(0));
	int state(0);
	int states[5]{ 1,4,3,1,1 };
	Uint32 time = SDL_GetTicks();
	Uint32 time2wait = rand() % 5000;
	Uint32 time2click = 0;

	int color[5][4] =
	{
		0,0,0,255,
		255,0,0,255,
		0,255,0,255,
		0,0,255,255,
		255,255,0,255
	};

	while (active)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) active = false;
			if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN) state = states[state];
		}
		if (state == 1 && SDL_GetTicks() > time + time2wait) state = 2;
		if (state == 2) time2click = SDL_GetTicks() - time2wait;

		static char title[256];
		sprintf_s(title, 256, " | STATE %d | TIME2WAIT %d | TIME2CLICK %d | ", state, time2wait, time2click);
		SDL_SetWindowTitle(window, title);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, color[state][0], color[state][1], color[state][2], color[state][3]);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_Quit();
	return 0;
}
