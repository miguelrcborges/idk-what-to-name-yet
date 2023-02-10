#include "include.h"

int main(int argc, char *argv[]) {
	Game game = Game_create(argc, argv);
	Uint64 last_count = SDL_GetPerformanceCounter();

	while (1) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
				goto leave;
			//else 
			//	Game_process_event(&game, &e);
			
		}

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