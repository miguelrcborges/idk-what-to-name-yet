#include "include.h"

SDL_Rect Player_get_rect_wrapper(Animation animation, Position position,
			const Window *window) {
	switch (animation.animation) {
	case PLAYER_IDLE:
		return Player_idle_rect(position, window);
	case PLAYER_MOVE_UP:
		return Player_moving_up_rect(position, animation.frame, window);
	case PLAYER_MOVE_DOWN:
		return Player_moving_down_rect(position, animation.frame, window);
	case PLAYER_MOVE_RIGHT:
		return Player_moving_right_rect(position, animation.frame, window);
	case PLAYER_MOVE_LEFT:
		return Player_moving_left_rect(position, animation.frame, window);
	default:
		__builtin_unreachable();
	}
}

SDL_Rect Player_idle_rect(Position position, const Window *window) {
	SDL_Rect rect = {
		.x = window->window_padding.width + position.x * (window->tile_side + window->tile_gap) + window->player_margin,
		.y = window->window_padding.height + position.y * (window->tile_side + window->tile_gap) + window->player_margin,
		.w = window->player_side,
		.h = window->player_side
	};

	return rect;
}

SDL_Rect Player_moving_up_rect(Position position, char frame, const Window *window) {
	SDL_Rect rect = {
		.x = window->window_padding.width + position.x * (window->tile_side + window->tile_gap) + window->player_margin,
		.y = window->window_padding.height + position.y * (window->tile_side + window->tile_gap) + window->player_margin + window->tile_side * frame / PLAYER_MOVE_FRAMES,
		.w = window->player_side,
		.h = window->player_side
	};

	return rect;
}

SDL_Rect Player_moving_down_rect(Position position, char frame, const Window *window) {
	SDL_Rect rect = {
		.x = window->window_padding.width + position.x * (window->tile_side + window->tile_gap) + window->player_margin,
		.y = window->window_padding.height + position.y * (window->tile_side + window->tile_gap) + window->player_margin - window->tile_side * frame / PLAYER_MOVE_FRAMES,
		.w = window->player_side,
		.h = window->player_side
	};

	return rect;
}

SDL_Rect Player_moving_left_rect(Position position, char frame, const Window *window) {
	SDL_Rect rect = {
		.x = window->window_padding.width + position.x * (window->tile_side + window->tile_gap) + window->player_margin + window->tile_side * frame / PLAYER_MOVE_FRAMES,
		.y = window->window_padding.height + position.y * (window->tile_side + window->tile_gap) + window->player_margin,
		.w = window->player_side,
		.h = window->player_side
	};

	return rect;
}

SDL_Rect Player_moving_right_rect(Position position, char frame, const Window *window) {
	SDL_Rect rect = {
		.x = window->window_padding.width + position.x * (window->tile_side + window->tile_gap) + window->player_margin - window->tile_side * frame / PLAYER_MOVE_FRAMES,
		.y = window->window_padding.height + position.y * (window->tile_side + window->tile_gap) + window->player_margin,
		.w = window->player_side,
		.h = window->player_side
	};

	return rect;
}
