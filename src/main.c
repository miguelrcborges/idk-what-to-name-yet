#include "include.h"

int main(int argc, char *argv[]) {
	Game game = Game_create(argc, argv);
	SDL_Delay(4000);
	Game_destroy(&game);
	return 0;
}