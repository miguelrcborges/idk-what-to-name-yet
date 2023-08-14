# idk-what-to-name-yet

Fast 1vs1 "fighting-game like" game. This game is inspired
on [One Step From Eden](https://store.steampowered.com/app/960690/One_Step_From_Eden/) and Mega Man Battle Network.


# Dependencies
- SDL2
- SDL2_TTF


# Building

Run ```make release```.
When compiling this, make sure you have SDL2 and SDL2_TTF installed 
(and their development versions if the previous packages don't ship the
development libraries on your distro).


# ToDos

- [x] Player movement
- [ ] Game main menu (doesn't jump directly to the game)
- [ ] Costumization at runtime instead of compile time
- [ ] SFX
- [ ] Networking for online multiplayer