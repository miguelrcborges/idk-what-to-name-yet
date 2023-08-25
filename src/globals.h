/*
 * Header dependencies:
 *
 * <SDL2/SDL_ttf.>
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#ifndef MAIN
#define DEF extern 
#else
#define DEF
#endif

DEF TTF_Font *jb_pt128;
DEF SDL_Texture *local_tx;
DEF SDL_Texture *online_tx;
DEF SDL_Texture *options_tx;

#endif
