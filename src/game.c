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
		window_padding_x = width * 10 / 100;
		window_padding_y = (height - (tile_side * 4 + tile_gap * 3)) / 2;
	} else {
		tile_side = (height - (height * 30 / 100)) / 4;
		tile_gap = (height - (height * 90 / 100)) / 3;
		window_padding_y = height * 10 / 100;
		window_padding_x = (width - (tile_side * 4 + tile_gap * 3)) / 2;
	}
	
	const int player_margin = tile_side * 15 / 100;

	Game game = {
		.window = { 
			.window = window,
			.renderer = renderer, 
			.window_size = { width, height },
			.window_padding = { window_padding_x, window_padding_y },
			.tile_side = tile_side,
			.tile_gap = tile_gap,
			.player_margin = player_margin,
			.player_side = tile_side - player_margin * 2,
		},

		.players_position = { { 1, 1 }, { 6, 1 } },
		.players_animation_frame = { 0 },
		.players_binds = { {'w', 's', 'a', 'd'}, {'i', 'k', 'j', 'l'} },
		.players_render_function = { Player_idle_rect, Player_idle_rect },
		.frame_rate = 120,
	};

	return game;
}

void Game_destroy(Game *const game) {
	SDL_DestroyRenderer(game->window.renderer);
	SDL_DestroyWindow(game->window.window);
	SDL_Quit();
}

void Game_process_event(Game *const game, const SDL_Event *const e) {
	if (e->type != SDL_KEYDOWN || e->key.repeat) return;
	for (int i = 0; i < 2; i++) {
		if (e->key.keysym.sym == game->players_binds[i].up) {
			if (game->players_animation_frame[i]) return;
			game->players_position[i].y--;
			if (game->players_position[i].y < 0) game->players_position[i].y = 0;
			game->players_animation_frame[i] = PLAYER_MOVE_FRAMES;

		} else if (e->key.keysym.sym == game->players_binds[i].down) {
			if (game->players_animation_frame[i]) return;
			game->players_position[i].y++;
			if (game->players_position[i].y > 3) game->players_position[i].y = 3;
			game->players_animation_frame[i] = PLAYER_MOVE_FRAMES;

		} else if (e->key.keysym.sym == game->players_binds[i].left) {
			if (game->players_animation_frame[i]) return;
			game->players_position[i].x--;
			if (game->players_position[i].x < 4 * i) game->players_position[i].x = 4 * i;
			game->players_animation_frame[i] = PLAYER_MOVE_FRAMES;

		} else if (e->key.keysym.sym == game->players_binds[i].right) {
			if (game->players_animation_frame[i]) return;
			game->players_position[i].x++;
			if (game->players_position[i].x > 4 * i + 3) game->players_position[i].x = 4 * i + 3;
			game->players_animation_frame[i] = PLAYER_MOVE_FRAMES;
		}
	}
}

void Game_render(const Game *const game) {
	SDL_SetRenderDrawColor(game->window.renderer, GAME_BACKGROUND_COLOR.r, GAME_BACKGROUND_COLOR.g, GAME_BACKGROUND_COLOR.b, GAME_BACKGROUND_COLOR.a);
	SDL_RenderClear(game->window.renderer);

	SDL_Rect rect = { 0, 0, game->window.tile_side, game->window.tile_side };
	
	SDL_SetRenderDrawColor(game->window.renderer, PLAYER_ONE_COLOR.r, PLAYER_ONE_COLOR.g, PLAYER_ONE_COLOR.b, PLAYER_ONE_COLOR.a);
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			rect.x = game->window.window_padding.width + x * (game->window.tile_side + game->window.tile_gap);
			rect.y = game->window.window_padding.height + y * (game->window.tile_side + game->window.tile_gap);
			SDL_RenderDrawRect(game->window.renderer, &rect);
		}
	}
	SDL_RenderFillRect(game->window.renderer, &(game->players_animation_rect[0]));

	SDL_SetRenderDrawColor(game->window.renderer, PLAYER_TWO_COLOR.r, PLAYER_TWO_COLOR.g, PLAYER_TWO_COLOR.b, PLAYER_TWO_COLOR.a);
	for (int x = 4; x < 8; x++) {
		for (int y = 0; y < 4; y++) {
			rect.x = game->window.window_padding.width + x * (game->window.tile_side + game->window.tile_gap);
			rect.y = game->window.window_padding.height + y * (game->window.tile_side + game->window.tile_gap);
			SDL_RenderDrawRect(game->window.renderer, &rect);
		}
	}
	SDL_RenderFillRect(game->window.renderer, &(game->players_animation_rect[1]));

	SDL_RenderPresent(game->window.renderer);
}