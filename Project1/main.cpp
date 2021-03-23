#include <SDL.h>
#include <SDL_image.h>
#include<stdbool.h>
#include <stdio.h>
#include <string>
#include <SDL_mixer.h>
#include<iostream>
using namespace std;

typedef struct {
	int x;
	int y;
	int r;
	int speed;

}Spot;
void moveSpot(Spot* spot) {
	spot->x = spot->x + spot->speed;
	if (spot->x >= 800) {
		spot->x = 0;
	}
}
void drawSpot(Spot* spot, SDL_Renderer* rend, SDL_Texture* circle) {
	SDL_Rect rect;
	rect.x = spot->x;
	rect.y = spot->y;
	rect.w = spot->r;
	rect.h = spot->r;
	SDL_RenderCopy(rend, circle, NULL, &rect);
}
int main(int agrc, char* agrv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("SDL ttr", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_Surface* blackSurface = SDL_LoadBMP("dot.bmp");
	SDL_Surface* circleSurface = SDL_LoadBMP("agujero.bmp");
	SDL_Surface* tesla = SDL_LoadBMP("tesla.bmp");
	SDL_Rect rect2;

	rect2.x = 200;
	rect2.y = 0;

	SDL_Texture* black = SDL_CreateTextureFromSurface(rend, blackSurface);
	SDL_Texture* circle = SDL_CreateTextureFromSurface(rend, circleSurface);
	SDL_Rect rectWindow;
	/*SDL_Rect rect;*/
	rectWindow.x = 0;
	rectWindow.y = 0;
	rectWindow.w = 800;
	rectWindow.h = 600;
	/*rect.x = 100;
	rect.y = 100;
	rect.w = 800;
	rect.h = 600;*/


	/*SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(rend);*/
	Spot spots[100];
	int i;
	for (i = 0; i < 10; i++) {
		spots[i].x = rand() % 800;
		spots[i].y = rand() % 600;
		spots[i].r = 100;
		spots[i].speed = rand() % 2 + 1;

	}


	bool quit = false;
	SDL_Event event;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music* sound = Mix_LoadMUS("music.wav");

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		SDL_RenderCopy(rend, black, NULL, &rectWindow);
		Mix_PlayMusic(sound, 1);
		for (i = 0; i < 100; i++) {
			drawSpot(&spots[i], rend, circle);
			moveSpot(&spots[i]);
		}
		if (event.type == SDL_MOUSEMOTION) {
			rect2.y = event.motion.y;
			SDL_FillRect(surface, NULL, 0);
			SDL_BlitSurface(tesla, NULL, surface, &rect2);

			SDL_UpdateWindowSurface(window);
		}
		/*SDL_RenderCopy(rend, circle, NULL, &rect);*/
		SDL_RenderPresent(rend);
		SDL_Delay(5);

	}
	SDL_DestroyWindow;
	return 0;
}