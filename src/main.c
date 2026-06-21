#ifndef SHMUP_C
#define SHMUP_C
#include "background.h"
#include "bullets.h"
#include "enemies.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "textures.h"
#include "windowscale.h"
#include "word-wrap.h"
#include <dialogue.h>
#include <stdio.h>
#include <waves.h>
RenderTexture2D pixel_render_target;

#define BUTTON_GAP 16
#define BUTTON_COUNT 6
int title_selected = 0;
void Tutorial() {
  bool unpressed = false;
  Rectangle tutorial_rect = {8, 8, pixel_render_target.texture.width - 16,
                             pixel_render_target.texture.height - 16};
  while (!WindowShouldClose()) {
    BeginTextureMode(pixel_render_target);
    ClearBackground(GRAY);
    if (unpressed && IsKeyPressed(KEY_ENTER)) {
      return;
    }
    if (IsKeyUp(KEY_ENTER)) {
      unpressed = true;
    }

#define TUTORIAL                                                               \
  "THis is the tutorial textTHis is the tutorial textTHis is the tutorial "    \
  "textTHis is the tutorial text....THis is the tutorial text."
    DrawTextBoxed(GetFontDefault(), TUTORIAL, tutorial_rect, 10, 2, WHITE);
    EndTextureMode();
    DrawToWindow(pixel_render_target);
  }
}
int TitleScreen() {
  bool unpressed = false;
  const char *buttons[BUTTON_COUNT] = {"Level 1",    "Level 2",  "Level 3",
                                       "Fullscreen", "Tutorial", "Quit"};
  printf("title\n");

  while (!WindowShouldClose()) {
    printf("title draw\n");

    BeginTextureMode(pixel_render_target);
    ClearBackground(GRAY);
    DrawText("Game name", 16, 16, 32, WHITE);
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
      title_selected = Clamp(title_selected - 1, 0, BUTTON_COUNT - 1);
    }
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
      title_selected = Clamp(title_selected + 1, 0, BUTTON_COUNT - 1);
    }
    if (unpressed && IsKeyPressed(KEY_ENTER)) {
      return title_selected;
    }
    if (IsKeyUp(KEY_ENTER)) {
      unpressed = true;
    }

    for (int i = 0; i < BUTTON_COUNT; i++) {
      Color draw_color = (title_selected == i) ? RED : WHITE;
      DrawText(buttons[i], 16, 64 + BUTTON_GAP * i, 20, draw_color);
    }
    EndTextureMode();
    DrawToWindow(pixel_render_target);
  }
  return -1;
}

// TODO use this
void PlayLevel(char *levelname) {
  wvs_LoadLevel(levelname);
  bool looping = true;
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
}

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
  tex_Init();
  pixel_render_target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

  while (!WindowShouldClose()) {
    int title_result = TitleScreen();
    switch (title_result) {
    case 0:
      PlayLevel("1.txt");
      break;
    case 1:
      printf("level 2");
      break;
    case 2:
      printf("level 3");
      break;
    case 3:
      ToggleFullscreen();
      break;
    case 4:
      Tutorial();
      break;
    case 5:
      CloseWindow();
      break;
    }
  }
}

#endif
