#include "bullets.h"
#include "enemies.h"
#include "player.c"
#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "windowscale.h"

int main() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  float backgroundSpeed = 150;

  CreateWindow();
  SearchAndSetResourceDir("resources");

  enm_Init();
  bul_Init();
  ply_Init();
  RenderTexture2D pixel_render_target =
      LoadRenderTexture(game_width, game_height);
  Texture2D background = LoadTexture("background.png");

  while (!WindowShouldClose()) {

    moveBullets(GetFrameTime(), game_width, game_height);
    enm_Update(GetFrameTime());
    bul_Update(GetFrameTime(), game_width, game_height);
    ply_Update();

    BeginTextureMode(pixel_render_target);
    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);
    int bgOffset = (int)(GetTime() * backgroundSpeed) % background.height;
    DrawTexture(background, 0, bgOffset, WHITE);
    DrawTexture(background, 0, bgOffset - game_height, WHITE);

    if (IsKeyPressed(KEY_E)) {
      Vector2 newenmpos = {50, 50};
      enm_New(newenmpos, 10);
    }

    enm_Draw();
    bul_Draw();
    ply_Draw();

    EndTextureMode();

    DrawToWindow(pixel_render_target);
  }

  UnloadTexture(wabbit);
  CloseWindow();
  return 0;
}
