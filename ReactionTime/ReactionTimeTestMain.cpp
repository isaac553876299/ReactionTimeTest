#include <iostream>
#include "SDL.h"
#include <time.h>
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 300, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	srand(time(0));
	Uint32 state(0), time(0), last(0), best(1000);
	int color[3][4]{ 0,0,0,255,255,0,0,255,0,255,0,255 };
	while (1)
	{
		if (state == 1 && SDL_GetTicks() > time) state = 2;
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) return 0;
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				switch (state)
				{
				case 0:
					time = SDL_GetTicks() + rand() % 5000;
					last = 0;
					state = 1;
					break;
				case 1:
					state = 0;
					break;
				case 2:
					last = SDL_GetTicks() - time;
					if (last < best) best = last;
					state = 0;
					break;
				}
			}
		}
		static char title[256];
		sprintf_s(title, 256, " | best %d | last %d | ", best, last);
		SDL_SetWindowTitle(window, title);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, color[state][0], color[state][1], color[state][2], color[state][3]);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_Quit();
	return 0;
}
