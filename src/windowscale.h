#include "raylib.h"

int game_width = 360;
int game_height = 640;

void CreateWindow() {
  InitWindow(game_width, game_height, "shmup");
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

  Rectangle destRec = {0.0f, 0.0f, screen_width, screen_height};

  Vector2 origin = {0.0f, 0.0f};
  bool smoothOn = true;
  if (smoothOn) {
    DrawTexturePro(source.texture, sourceRec, destRec, origin, 0.0f, WHITE);
  }
  DrawFPS(GetScreenWidth() - 95, 10);
  EndDrawing();
}
