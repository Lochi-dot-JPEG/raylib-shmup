#include "bullets.h"
#include "enemies.h"
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "windowscale.h"

Vector2 bulletDirections[3] = {{0.176, -0.984}, {0, -1}, {-0.176, -0.984}};
void createPlayerBullets(Vector2 playerPos, float speed, float delta) {
  for (int i = 0; i < 3; i++) {
    Vector2 dir = {bulletDirections[i].x * speed,
                   bulletDirections[i].y * speed};
    createBulletAtPoint(playerPos, dir, delta);
  }
}

int main() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  float backgroundSpeed = 150;

  enm_Init();
  bul_Init();

  CreateWindow();
  SearchAndSetResourceDir("resources");

  RenderTexture2D pixel_render_target =
      LoadRenderTexture(game_width, game_height);
  Texture wabbit = LoadTexture("wabbit_alpha.png");
  Texture2D background = LoadTexture("background.png");
  Vector2 wabbitSize = {wabbit.width, wabbit.height};

  Vector2 wabbitPos = {0, 0};
  int wabbitSpeed = 500;

  int shooting = 0;
  while (!WindowShouldClose()) {

    moveBullets(GetFrameTime(), game_width, game_height);
    enm_Update(GetFrameTime());
    bul_Update(GetFrameTime(), game_width, game_height);

    if (shooting == 3) {
      Vector2 pos = {wabbitPos.x + wabbitSize.x / 2, wabbitPos.y};
      createPlayerBullets(pos, bulletSpeed, GetFrameTime());
      shooting = 0;
    }
    shooting++;

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
    if (IsKeyDown(KEY_D)) {
      wabbitPos.x += wabbitSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_A)) {
      wabbitPos.x -= wabbitSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_W)) {
      wabbitPos.y -= wabbitSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S)) {
      wabbitPos.y += wabbitSpeed * GetFrameTime();
    }
    wabbitPos.x = Clamp(wabbitPos.x, 0, game_width - wabbitSize.x);
    wabbitPos.y = Clamp(wabbitPos.y, 0, game_height - wabbitSize.y);

    enm_Draw();
    bul_Draw();

    DrawTexture(wabbit, (int)wabbitPos.x, (int)wabbitPos.y, WHITE);

    EndTextureMode();

    DrawToWindow(pixel_render_target);
  }

  UnloadTexture(wabbit);
  CloseWindow();
  return 0;
}
