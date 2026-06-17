#ifndef WINSCALE_H
#define WINSCALE_H
#include "raylib.h"

#ifndef GAME_WIDTH
#define GAME_WIDTH 240
#endif
#ifndef GAME_HEIGHT
#define GAME_HEIGHT 480
#endif
void CreateWindow();
void DrawToWindow(RenderTexture2D source);
#endif
