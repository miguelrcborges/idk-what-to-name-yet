#include "include.h"

SDL_Rect Player_idle_rect(const Position position, const char _, const Window *const window) {
	SDL_Rect rect = {
		.x = window->window_padding.width + position.x * (window->tile_side + window->tile_gap) + window->player_margin,
		.y = window->window_padding.height + position.y * (window->tile_side + window->tile_gap) + window->player_margin,
		.w = window->player_side,
		.h = window->player_side
	};

	return rect;
}

SDL_Rect Player_moving_up_rect(const Position position, const char frame, const Window *const window) {
	SDL_Rect rect = {
		.x = window->window_padding.width + position.x * (window->tile_side + window->tile_gap) + window->player_margin,
		.y = window->window_padding.height + position.y * (window->tile_side + window->tile_gap) + window->player_margin + window->tile_side * frame / PLAYER_MOVE_FRAMES,
		.w = window->player_side,
		.h = window->player_side
	};

	return rect;
}

SDL_Rect Player_moving_down_rect(const Position position, const char frame, const Window *const window) {
	SDL_Rect rect = {
		.x = window->window_padding.width + position.x * (window->tile_side + window->tile_gap) + window->player_margin,
		.y = window->window_padding.height + position.y * (window->tile_side + window->tile_gap) + window->player_margin - window->tile_side * frame / PLAYER_MOVE_FRAMES,
		.w = window->player_side,
		.h = window->player_side
	};

	return rect;
}

SDL_Rect Player_moving_left_rect(const Position position, const char frame, const Window *const window) {
	SDL_Rect rect = {
		.x = window->window_padding.width + position.x * (window->tile_side + window->tile_gap) + window->player_margin + window->tile_side * frame / PLAYER_MOVE_FRAMES,
		.y = window->window_padding.height + position.y * (window->tile_side + window->tile_gap) + window->player_margin,
		.w = window->player_side,
		.h = window->player_side
	};

	return rect;
}

SDL_Rect Player_moving_right_rect(const Position position, const char frame, const Window *const window) {
	SDL_Rect rect = {
		.x = window->window_padding.width + position.x * (window->tile_side + window->tile_gap) + window->player_margin - window->tile_side * frame / PLAYER_MOVE_FRAMES,
		.y = window->window_padding.height + position.y * (window->tile_side + window->tile_gap) + window->player_margin,
		.w = window->player_side,
		.h = window->player_side
	};

	return rect;
}