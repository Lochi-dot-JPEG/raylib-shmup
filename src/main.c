#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "stdlib.h"
#include <stdio.h>

#define MAX_BULLETS 50000

typedef struct Bullet {
  Vector2 position;
  Vector2 velocity;
  Color color;
  bool disabled;
} Bullet;

void moveBullets(Bullet *bullets, int bulletCount, float delta, int winWidth,
                 int winHeight) {
  for (int i = 0; i < bulletCount; i++) {
    Bullet b = bullets[i];
    if (!b.disabled) {
      bullets[i].position.x += b.velocity.x * delta;
      bullets[i].position.y += b.velocity.y * delta;
      if (b.position.x < 0 || b.position.x > winWidth || b.position.y < 0 ||
          b.position.y > winHeight) {
        bullets[i].disabled = true;
      }
    }
  }
}
Vector2 bulletDirections[3] = {{0.309, -0.951}, {0, -1}, {-0.309, -0.951}};

void createPlayerBullets(Vector2 origin, Bullet *bullets, int *bulletCount,
                         float speed, float delta) {
  for (int i = 0; i < 3; i++) {
    Vector2 dir = bulletDirections[i];
    bullets[*bulletCount].position = origin;
    bullets[*bulletCount].velocity.x = dir.x * speed;
    bullets[*bulletCount].velocity.y = dir.y * speed;
    bullets[*bulletCount].color = RED;
    bullets[*bulletCount].disabled = false;
    *bulletCount += 1;
  }
}

int main() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  int windowW = 800;
  int windowH = 600;
  Bullet *bullets = (Bullet *)RL_CALLOC(MAX_BULLETS, sizeof(Bullet));
  int bulletCount = 0;
  int bulletRadius = 10;
  float bulletSpeed = 800;
  int bulletRows = 3;
  int bulletAngle = 5;
  Color bulletColor = RED;

  InitWindow(windowW, windowH, "shmup");
  SetTargetFPS(60);
  SearchAndSetResourceDir("resources");
  Texture wabbit = LoadTexture("wabbit_alpha.png");
  Vector2 wabbitSize = {wabbit.width, wabbit.height};

  Vector2 wabbitPos = {0, 0};
  int wabbitSpeed = 500;

  int shooting = 0;
  while (!WindowShouldClose()) {
    moveBullets(bullets, bulletCount, GetFrameTime(), windowW, windowH);

    if (shooting == 3) {
      createPlayerBullets(wabbitPos, bullets, &bulletCount, bulletSpeed,
                          GetFrameTime());
      shooting = 0;
    }
    shooting++;

    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);

    // draw some text using the default font
    DrawText("Hello Raylib", 200, 200, 20, WHITE);

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
    wabbitPos.x = Clamp(wabbitPos.x, 0, windowW - wabbitSize.x);
    wabbitPos.y = Clamp(wabbitPos.y, 0, windowH - wabbitSize.y);

    int drawnBullets = 0;
    // Draw bullets
    for (int i = 0; i < bulletCount; i++) {
      if (bullets[i].disabled) {
        continue;
      }
      drawnBullets++;
      Vector2 pos = bullets[i].position;
      DrawCircle(pos.x, pos.y, bulletRadius, bullets[i].color);
    }
    char str[8];
    snprintf(str, sizeof(str), "%d", drawnBullets);
    DrawText(str, 500, 200, 20, WHITE);

    DrawTexture(wabbit, (int)wabbitPos.x, (int)wabbitPos.y, WHITE);

    EndDrawing();
  }

  UnloadTexture(wabbit);
  CloseWindow();
  return 0;
}
