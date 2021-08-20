# Sepples game engine

A 2D/3D game engine purely for learning purposes. The engine has been heavily influenced by the following game engine series:
* [3D Game Engine Development Tutorial](https://www.youtube.com/playlist?list=PLEETnX-uPtBXP_B2yupUKlflXBznWIlL5) by thebennybox
* [Hazel game engine series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT) by TheCherno

## Dependencies
All dependencies will be attempted to be added as git submodules under the vendor folder and built via the project Makefile.

* SDL2 2.0.12 or greater
* OpenGL
* Glad
* Assimp
* spdlog

## Building/running
```bash
make
./build/game_engine
```

## Attribution
* stb\_image.h: https://github.com/nothings/stb
* Test model: https://sketchfab.com/3d-models/survival-guitar-backpack-low-poly-799f8c4511f84fab8c3f12887f7e6b36
