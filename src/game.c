#include "include.h"

Game Game_create(const int argc, char *const *const argv) {
	char fullscreen = 1, vsync = 0;
	int height = 0, width = 0;
	int window_flags = SDL_WINDOW_SHOWN;
	int renderer_flags = SDL_RENDERER_ACCELERATED;

	for (int i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "-w")) {
			fullscreen = 0;
		} else if (!strcmp(argv[i], "-v")) {
			vsync = 1;
		} else if (!strcmp(argv[i], "-f")) {
			fullscreen = 1;
		} else if (!strcmp(argv[i], "-w")) {
			if (i + 1 < argc) {
				width = atoi(argv[i + 1]);
			}
		} else if (!strcmp(argv[i], "-h")) {
			if (i + 1 < argc) {
				height = atoi(argv[i + 1]);
			}
		}
	}

	if (fullscreen)
		window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

	if (vsync)
		renderer_flags |= SDL_RENDERER_PRESENTVSYNC;
	
	if (!fullscreen && (width == 0 || height == 0)) {
		width = 1600;
		height = 900;
	}

	if (SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Failed at SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Window *window = SDL_CreateWindow("idk what to name yet", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
	if (!window) {
		SDL_Log("Failed at SDL_CreateWindow: %s", SDL_GetError());
		exit(2);
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if (!renderer) {
		SDL_Log("Failed at SDL_CreateRenderer: %s", SDL_GetError());
		exit(3);
	}

	if (fullscreen) {
		SDL_GetWindowSize(window, &width, &height);
	}

	char limited_on_width = width / 2 > height ? 0 : 1;
	int tile_side, tile_gap, window_padding_x, window_padding_y;
	if (limited_on_width) {
		tile_side = (width - (width * 30 / 100)) / 8;
		tile_gap = (width - (width * 90 / 100)) / 7;
		window_padding_x = width * 20 / 100;
		window_padding_y = (height - (tile_side * 4 + tile_gap * 3)) / 2;
	} else {
		tile_side = (height - (height * 30 / 100)) / 4;
		tile_gap = (height - (height * 90 / 100)) / 3;
		window_padding_y = height * 20 / 100;
		window_padding_x = (width - (tile_side * 4 + tile_gap * 3)) / 2;
	}

	Game game = {
		.window = { 
			.window = window,
			.renderer = renderer, 
			.window_size = { width, height },
			.window_padding = { window_padding_x, window_padding_y },
			.tile_side = tile_side,
			.tile_gap = tile_gap,
			.player_margin = tile_side * 15 / 100
		},

		.players_position = { { 1, 1 }, { 6, 1 } },
		.players_animation_frame = { 0 },
		.player_binds = { {'w', 'a', 's', 'd'}, {'i', 'j', 'k', 'l'} },
		.frame_rate = 120,
	};

	return game;
}

void Game_destroy(Game *const game) {
	SDL_DestroyRenderer(game->window.renderer);
	SDL_DestroyWindow(game->window.window);
	SDL_Quit();
}