#include "include.h"

int main(int argc, char *argv[]) {
	Game game = Game_create(argc, argv);
	Uint64 last_count = SDL_GetPerformanceCounter();

	while (1) {
		for (int i = 0; i < 2; i++)
			if (game.players_animations[i].frame) {
				game.players_animations[i].frame--;
				if (!game.players_animations[i].frame)
					game.players_animations[i].frame = PLAYER_IDLE;
			}

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				goto leave;

			Game_process_event(&game, &e);
		}

		for (int i = 0; i < 2; i++)
			game.players_animation_rect[i] = Player_get_rect_wrapper(game.players_animations[i],
					game.players_position[i], &game.window);

		Game_render(&game);

		const Uint64 current_count = SDL_GetPerformanceCounter();
		const Uint64 elapsed_time = (current_count - last_count) / SDL_GetPerformanceFrequency() * 1000;
		SDL_Delay(1000 / game.frame_rate - elapsed_time);
		last_count = current_count;
	}

leave:
	Game_destroy(&game);
	return 0;
}
