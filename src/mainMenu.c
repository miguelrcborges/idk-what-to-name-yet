#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_keycode.h>

#include <SDL2/SDL_ttf.h>

#include "mainMenu.h"
#include "scenes.h"
#include "globals.h"

enum MAIN_MENU_CONSTANTS {
	MAIN_MENU_FRAME_RATE = 30,
	MAIN_MENU_BG_COLOR_R = 0x16,
	MAIN_MENU_BG_COLOR_G = 0x16,
	MAIN_MENU_BG_COLOR_B = 0x16,
	MAIN_MENU_BG_COLOR_A = 0xff,

	MAIN_MENU_OPTION_R = 0xaa,
	MAIN_MENU_OPTION_G = 0xaa,
	MAIN_MENU_OPTION_B = 0xaa,
	MAIN_MENU_OPTION_A = 0xff,

	MAIN_MENU_OPTION_FOCUS_R = 0xdd,
	MAIN_MENU_OPTION_FOCUS_G = 0xdd,
	MAIN_MENU_OPTION_FOCUS_B = 0xdd,
	MAIN_MENU_OPTION_FOCUS_A = 0xff,
};

enum MAIN_MENU_OPTIONS {
	LOCAL_MULTIPLAYER,
	ONLINE_MULTIPLAYER,
	SETTINGS,
	NUMBER_OF_OPTIONS,
};


int mainMenu(SDL_Window *win, SDL_Renderer *ren) {
	SDL_Event e;
	Uint64 last_count = SDL_GetPerformanceCounter();
	int option = 0;

	while (1) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return QUIT;
			} else if (e.type == SDL_KEYDOWN && !e.key.repeat) {
				if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN) {
					if (option + 1 < NUMBER_OF_OPTIONS) 
						++option;
				} else if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_UP) {
					if (option - 1 >= 0) {
						--option;
					}
				} 
			}
		}

		SDL_SetRenderDrawColor(
			ren,
			MAIN_MENU_BG_COLOR_R,
			MAIN_MENU_BG_COLOR_G, 
			MAIN_MENU_BG_COLOR_B, 
			MAIN_MENU_BG_COLOR_A
		);
		SDL_RenderClear(ren);

		int ww, wh;
		SDL_Rect r;
		SDL_GetWindowSize(win, &ww, &wh);
		r.h = wh / 10;
		// r.w = ww / 2;
		r.w = r.h * 5 / 2;
		for (int i = 0; i < NUMBER_OF_OPTIONS; ++i) {
			if (option == i) {
				SDL_SetRenderDrawColor(
					ren, 
					MAIN_MENU_OPTION_FOCUS_R,
					MAIN_MENU_OPTION_FOCUS_G,
					MAIN_MENU_OPTION_FOCUS_B,
					MAIN_MENU_OPTION_FOCUS_A
				);
			} else {
				SDL_SetRenderDrawColor(
					ren, 
					MAIN_MENU_OPTION_R,
					MAIN_MENU_OPTION_G,
					MAIN_MENU_OPTION_B,
					MAIN_MENU_OPTION_A
				);
			}
			r.x = ww / 4;
			r.y = i * (r.h + 50) + wh / 2;
			// SDL_RenderFillRect(ren, &r);
			SDL_RenderCopy(ren, local_tx, NULL, &r);
		}

		SDL_RenderPresent(ren);
		Uint64 current_count = SDL_GetPerformanceCounter();
		Uint64 elapsed_time = (current_count - last_count) * 1000 / SDL_GetPerformanceCounter();
		SDL_Delay(1000 / MAIN_MENU_FRAME_RATE - elapsed_time);
		last_count = current_count;
	}

	return QUIT;
}
