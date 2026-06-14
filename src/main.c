#include "background.c"
#include "bullets.h"
#include "enemies.c"
#include "player.c"
#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "windowscale.h"
#include <waves.c>

int main() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  CreateWindow();
  SearchAndSetResourceDir("resources");

  enm_Init();
  bul_Init();
  ply_Init();
  wvs_Init();
  bkg_Init();
  RenderTexture2D pixel_render_target =
      LoadRenderTexture(game_width, game_height);

  while (!WindowShouldClose()) {

    moveBullets(GetFrameTime(), game_width, game_height);
    bool active_enemies = enm_Update(GetFrameTime());

    bul_Update(GetFrameTime(), game_width, game_height);
    ply_Update();
    wvs_Update(active_enemies);

    BeginTextureMode(pixel_render_target);
    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);

#if DEBUG
    if (IsKeyPressed(KEY_E)) {
      Vector2 newenmpos = {50, 50};
      enm_New(newenmpos, "spray");
    }
    if (IsKeyPressed(KEY_N)) {
      wvs_NextWave();
    }
#endif

    bkg_Draw(GetFrameTime());
    enm_Draw();
    bul_Draw();
    ply_Draw();

    wvs_DrawDialogue();

    EndTextureMode();

    DrawToWindow(pixel_render_target);
  }

  UnloadTexture(wabbit);
  CloseWindow();
  return 0;
}
