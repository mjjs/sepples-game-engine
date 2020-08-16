# Wolfenstein3D Clone
This branch contains a Wolfenstein3D clone made with this game engine.
This game is only a proof of concept to test the game engine in its current state, and the code contains ugly hacks and
other workarounds. After this game is ready, the game engine development will continue and the shortcomings of the engine met during this game's development will be fixed.

## Textures/Sprites
The textures are unfortunately not part of this repository, as they are copyrighted.

The textures need to be saved into `res/textures`. The wall texture should be a file called `WolfCollection.png` which contains all of the Wolfenstein textures in a 4x4 grid, each texture being 128x128 pixels.

The enemy, gun and medkit sprites should be named the same way as the sprites in the original Wolfenstein code.


## Building/running
```bash
make
./build/game_engine
```

## Attribution
* stb\_image.h: https://github.com/nothings/stb
* Test model: https://sketchfab.com/3d-models/survival-guitar-backpack-low-poly-799f8c4511f84fab8c3f12887f7e6b36
