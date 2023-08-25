#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#include <SDL2/SDL_ttf.h>

#define MAIN
#include "globals.h"
#include "exitcodes.h"
#include "scenes.h"
#include "mainMenu.h"

#define STRFY(x) #x
#define STRFYCON(x) STRFY(x)
#define AT " in " __FILE__ ":" STRFYCON(__LINE__)

SDL_Texture *makeTextTexture(SDL_Renderer *ren, TTF_Font *f, const char *t, SDL_Color c) {
	SDL_Surface *tmp = TTF_RenderText_Solid(f, t, c);
	if (tmp == NULL) {
		return NULL;
	}
	SDL_Texture *r = SDL_CreateTextureFromSurface(ren, tmp);
	SDL_FreeSurface(tmp);
	return r; 
}

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Error" AT ": %s", SDL_GetError());
		return SDL_INIT_ERROR;
	}
	if (TTF_Init()) {
		SDL_Log("Error" AT ": %s", SDL_GetError());
		return TTF_INI_ERROR;
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
		TTF_Quit();
		return SDL_WINDOW_CREATION_ERROR;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, renflags);
	if (ren == NULL) {
		SDL_Log("Error " AT ": %s", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		TTF_Quit();
		return SDL_RENDERER_CREATION_ERROR;
	}

	jb_pt128 = TTF_OpenFont("assets/JetBrainsMono-Medium.ttf", 512);
	if (jb_pt128 == NULL) {
		SDL_Log("Error" AT ": %s", SDL_GetError());
		goto close;
	}

	SDL_Color text_color = { 0xda, 0xda, 0xda, 0xff };
	local_tx = makeTextTexture(ren, jb_pt128, "Local", text_color);
	if (local_tx == NULL) {
		SDL_Log("Error" AT ": %s", SDL_GetError());
		goto close;
	}

	online_tx = makeTextTexture(ren, jb_pt128, "Online", text_color);
	if (online_tx == NULL) {
		SDL_Log("Error" AT ": %s", SDL_GetError());
		goto close;
	}

	options_tx = makeTextTexture(ren, jb_pt128, "Options", text_color);
	if (options_tx == NULL) {
		SDL_Log("Error" AT ": %s", SDL_GetError());
		goto close;
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
	TTF_Quit();
	return 0;
}
