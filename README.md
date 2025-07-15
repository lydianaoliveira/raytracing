# SDL2 Simple Example

This is a minimal SDL2 example for Windows. It opens a window and displays a color for 2 seconds.

## Build Instructions

1. Install SDL2 development libraries for Windows: https://github.com/libsdl-org/SDL/releases
2. Place SDL2 include and lib folders where your compiler can find them.
3. Compile with:

```
g++ sdl2_example.cpp -IC:/path/to/SDL2/include -LC:/path/to/SDL2/lib -lSDL2main -lSDL2 -o sdl2_example.exe
```

Replace `C:/path/to/SDL2` with your SDL2 location.

## Run

Double-click `sdl2_example.exe` or run in terminal:

```
./sdl2_example.exe
```
