#ifndef WINSCALE_H
#define WINSCALE_H
#include "raylib.h"

#define GAME_WIDTH 360
#define GAME_HEIGHT 640

void CreateWindow() {
  InitWindow(GAME_WIDTH, GAME_HEIGHT, "shmup");
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(60);
}
void DrawToWindow(RenderTexture2D source) {
  BeginDrawing();
  ClearBackground(BLACK);
  Rectangle sourceRec = {0.0f, 0.0f, (float)source.texture.width,
                         -(float)source.texture.height};

  int screen_width = GetRenderWidth();
  int screen_height = GetRenderHeight();

  float wScaled = screen_width;
  float hScaled = screen_height;

  // Correct aspect ratio
  if (screen_width / (float)screen_height > 9.0f / 16.0f) {
    wScaled = screen_height * 9.0f / 16.0f;
  }
  if (screen_width / (float)screen_height < 9.0f / 16.0f) {
    hScaled = screen_width * 16.0f / 9.0f;
  }

  float drawOffsetX = screen_width / 2.0f - wScaled / 2;
  float drawOffsetY = screen_height / 2.0f - hScaled / 2;

  Rectangle destRec = {drawOffsetX, drawOffsetY, wScaled, hScaled};

  Vector2 origin = {0.0f, 0.0f};

  DrawTexturePro(source.texture, sourceRec, destRec, origin, 0.0f, WHITE);
  DrawFPS(GetScreenWidth() - 95, 10);
  EndDrawing();
}
#endif
