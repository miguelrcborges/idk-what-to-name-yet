#ifndef INCLUDE_H
#define INCLUDE_H

#include "SDL2/SDL.h"

typedef struct Position {
	char x;
	char y;
} Position;

typedef struct Size {
	const int width;
	const int height;
} Size;

typedef struct Window {
	SDL_Window *const window;
	SDL_Renderer *const renderer;
	const Size window_size;
	const Size window_padding;
	const int tile_side;
	const int tile_gap;
	const int player_margin;
} Window;

typedef struct Hotkeys {
	const SDL_Keycode up;
	const SDL_Keycode down;
	const SDL_Keycode left;
	const SDL_Keycode right;
} Hotkeys;

typedef struct Game {
	Position players_position[2];
	const Hotkeys player_binds[2];
	char players_animation_frame[2];
	// array buffer de ataques
	SDL_Rect player_animation_rect[2];
	SDL_Rect (*player_render_function[2])(const Position position, const char frame, const Window *const window);
	Window window;
	const int frame_rate;
} Game;


#define GAME_BACKGROUND_COLOR 0x16, 0x16, 0x16, 0xFF
Game Game_create(const int argc, char *const *const argv);
void Game_process_event(Game *const game, const SDL_Event *const e);
void Game_render(const Game *const game);
void Game_destroy(Game *const game);

#endif