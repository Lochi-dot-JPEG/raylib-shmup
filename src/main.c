#ifndef SHMUP_C
#define SHMUP_C
#include "background.h"
#include "bullets.h"
#include "enemies.h"
#include "player.h"
#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "windowscale.h"
#include <dialogue.h>
#include <waves.h>

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
  dlg_Init();
  RenderTexture2D pixel_render_target =
      LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

  while (!WindowShouldClose()) {

    moveBullets(GetFrameTime(), GAME_WIDTH, GAME_HEIGHT);
    bool active_enemies = enm_Update(GetFrameTime());

    bul_Update(GetFrameTime(), GAME_WIDTH, GAME_HEIGHT);
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

    dlg_Draw();

    EndTextureMode();

    DrawToWindow(pixel_render_target);
  }

  CloseWindow();
  ply_Unload();
  bkg_Unload();
  return 0;
}
#endif
