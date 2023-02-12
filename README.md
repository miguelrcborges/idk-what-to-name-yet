# idk-what-to-name-yet

Fast 1vs1 "fighting-game like" game. This game is inspired on [One Step From Eden](https://store.steampowered.com/app/960690/One_Step_From_Eden/) and Mega Man Battle Network.

I started to develop this for learning purposes (mostly rendering and data oriented programming) and to possibly create a good, minimal FOSS game.

I started this codebase a few days earlier I created this repository. However, it was structured in a OOP-like way. I'm rewritting it in the previous mentioned paradigm. If you want to check the old source, you can download it [here](https://cdn.discordapp.com/attachments/944308156182429726/1073345107413184562/src.zip).

# Building

Run ```make release```.

When compiling this, make sure you have SDL2 (and SDL2-dev if the previous package doesn't ship the development libraries on your distro).
The makefile on the repository should work across all systems (assuming MingW64 on Windows). 
The windows folder holds the requirements to be built on windows.

The repo may not have the lastest version of SDL2. So, if you are on windows, considering replacing the content inside the windows folder 
with the latest development version you can download [here](https://github.com/libsdl-org/SDL/releases/latest).
Make sure that the SDL2.dll is in the same directory as the compiled binary.


# ToDos

- [x] Player movement
- [ ] Attacks ideas
- [ ] Attacks processing
- [ ] Attacks rendering
- [ ] Costumization at runtime instead of compile time
- [ ] SFX


#### Maybe ToDos
- [ ] Networking
- [ ] Game main menu (doesn't jump directly to the game)


# Possible optimizations that should be considered

Not sure if these will increase performance. It would be required doing afterbenchmarks after doing the implementation.

- Save recalculations of players' rects when there aren't new actions.
- Save board tile positions rect on memory.
- Don't store players' rects inside the Game struct and, instead, have a local Rect inside the render function which would have temporarily
each players value.