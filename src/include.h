#ifndef INCLUDE_H
#define INCLUDE_H

#include "config.h"

typedef struct Position {
	signed char x;
	signed char y;
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
	const int player_side;
} Window;

typedef struct Hotkeys {
	const SDL_Keycode up;
	const SDL_Keycode down;
	const SDL_Keycode left;
	const SDL_Keycode right;
} Hotkeys;

typedef struct Animation {
	unsigned char animation, frame;
} Animation;

typedef struct Game {
	const Hotkeys players_binds[2];
	Position players_position[2];
	Animation players_animations[2];
	// array buffer de ataques
	SDL_Rect players_animation_rect[2];
	Window window;
	const int frame_rate;
} Game;

Game Game_create(const int argc, char **argv);
void Game_process_event(Game *const game, const SDL_Event *const e);
void Game_render(const Game *const game);
void Game_destroy(Game *const game);

#define PLAYER_IDLE         0
#define PLAYER_MOVE_UP      1
#define PLAYER_MOVE_DOWN    2
#define PLAYER_MOVE_RIGHT   3
#define PLAYER_MOVE_LEFT    4

SDL_Rect Player_idle_rect(Position position, const Window *window);
SDL_Rect Player_moving_up_rect(Position position, char frame, const Window *window);
SDL_Rect Player_moving_down_rect(Position position, char frame, const Window *window);
SDL_Rect Player_moving_left_rect(Position position, char frame, const Window *window);
SDL_Rect Player_moving_right_rect(Position position, char frame, const Window *window);
SDL_Rect Player_get_rect_wrapper(Animation animation, Position position,
			const Window *window);

#endif
