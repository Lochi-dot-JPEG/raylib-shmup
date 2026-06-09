#ifndef PLAYER_C
#define PLAYER_C
// Frames until a new bullet is made
#include <stdio.h>
#define BULLET_COOLDOWN
#include <bullets.h>
#include <raylib.h>
#include <raymath.h>
#include <windowscale.h>

static int shooting = 0;
static int hp = 10;

Texture wabbit;
Vector2 wabbitSize;

Vector2 wabbitPos = {0, 0};
int wabbitSpeed = 500;
Vector2 bulletDirections[3] = {{0.176, -0.984}, {0, -1}, {-0.176, -0.984}};

void ply_Init() {
  wabbit = LoadTexture("wabbit_alpha.png");
  wabbitSize = (Vector2){wabbit.width, wabbit.height};
}

void createPlayerBullets(Vector2 playerPos, float speed, float delta) {
  for (int i = 0; i < 3; i++) {
    Vector2 dir = {bulletDirections[i].x * speed,
                   bulletDirections[i].y * speed};
    createBulletAtPoint(playerPos, dir, true);
  }
}

void ply_Draw() {
  DrawTexture(wabbit, (int)wabbitPos.x, (int)wabbitPos.y, WHITE);
  char str[8];
  snprintf(str, sizeof(str), "%d", hp);
  DrawText(str, 360 - 95, 80, 20, WHITE);
}

void ply_Update() {
  if (IsKeyDown(KEY_J) || IsKeyDown(KEY_Z)) {
    if (shooting == 5) {
      Vector2 pos = {wabbitPos.x + wabbitSize.x / 2, wabbitPos.y};
      createPlayerBullets(pos, bulletSpeed, GetFrameTime());
      shooting = 0;
    }
    shooting++;
  } else {
    shooting = 5;
  }

  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
    wabbitPos.x += wabbitSpeed * GetFrameTime();
  }
  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
    wabbitPos.x -= wabbitSpeed * GetFrameTime();
  }
  if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
    wabbitPos.y -= wabbitSpeed * GetFrameTime();
  }
  if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
    wabbitPos.y += wabbitSpeed * GetFrameTime();
  }
  wabbitPos.x = Clamp(wabbitPos.x, 0, game_width - wabbitSize.x);
  wabbitPos.y = Clamp(wabbitPos.y, 0, game_height - wabbitSize.y);

  Rectangle rec = {wabbitPos.x, wabbitPos.y, wabbitSize.x, wabbitSize.y};
  for (int b = 0; b < MAX_BULLETS; b++) {
    if (bullets[b].disabled || bullets[b].friendly) {
      continue;
    }

    if (CheckCollisionCircleRec(bullets[b].position, bulletRadius, rec)) {
      bullets[b].disabled = true;
      hp -= 1;
    }
  }
}

#endif
