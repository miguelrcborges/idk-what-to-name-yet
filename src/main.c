#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "exitcodes.h"
#include "scenes.h"
#include "mainMenu.h"

#define STRFY(x) #x
#define AT " in " __FILE__ ":" STRFY(__LINE__)

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Error " AT ": %s", SDL_GetError());
		return SDL_INIT_ERROR;
	}

	Uint32 winflags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	Uint32 renflags = SDL_RENDERER_PRESENTVSYNC;
	int width = 1600, height = 900;

	for (int i = 1; i < argc; i++) {
		if (SDL_strcmp(argv[i], "-win") == 0 || SDL_strcmp(argv[i], "--windowed") == 0) {
			winflags &= UINT32_MAX ^ SDL_WINDOW_FULLSCREEN_DESKTOP;
		} else if (SDL_strcmp(argv[i], "-f") == 0 || SDL_strcmp(argv[i], "--fullscreen") == 0) {
			winflags |= SDL_WINDOW_FULLSCREEN;
		} else if (SDL_strcmp(argv[i], "-v") == 0 || SDL_strcmp(argv[i], "--vsync") == 0) {
			renflags |= SDL_RENDERER_PRESENTVSYNC;
		} else if (SDL_strcmp(argv[i], "-nv") == 0 || SDL_strcmp(argv[i], "--no-vsync") == 0) {
			renflags &= UINT32_MAX ^ SDL_RENDERER_PRESENTVSYNC;
		} else if (SDL_strcmp(argv[i], "-w") == 0 || SDL_strcmp(argv[i], "--width") == 0) {
			if (i + i < argc) {
				++i;
				width = SDL_atoi(argv[i]);
			}
		} else if (SDL_strcmp(argv[i], "-h") == 0 || SDL_strcmp(argv[i], "--height") == 0) {
			if (i + i < argc) {
				++i;
				height = SDL_atoi(argv[i]);
			}
		}
	}

	SDL_Window *win = SDL_CreateWindow(
		"idk what to name yet",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		winflags
	);
	if (win == NULL) {
		SDL_Log("Error " AT ": %s", SDL_GetError());
		SDL_Quit();
		return SDL_WINDOW_CREATION_ERROR;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, renflags);
	if (ren == NULL) {
		SDL_Log("Error " AT ": %s", SDL_GetError());
		SDL_DestroyWindow(win);
		return SDL_RENDERER_CREATION_ERROR;
	}

	enum SCENE current_scene = MAIN_MENU;

	while (1) {
		switch (current_scene) {
		case QUIT:
			goto close;
		case MAIN_MENU:
			current_scene = mainMenu(win, ren);
			break;
		case IN_GAME: 
			break;
		default:
			__builtin_unreachable();
		}
	}

close:
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}