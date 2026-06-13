#ifndef PLAYER_C
#define PLAYER_C
// Frames until a new bullet is made
#include <bullets.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <windowscale.h>

#define PLAYER_SPAWN_BOTTOM_OF_SCREEN_GAP 50

static int shooting = 0;
static int hp = 10;
int max_hp = 10;

Texture wabbit;
Vector2 wabbit_size;

Vector2 wabbitPos = {0, 0};
int wabbitSpeed = 500;
Vector2 bulletDirections[3] = {{0.176, -0.984}, {0, -1}, {-0.176, -0.984}};

void ply_Init() {
  wabbit = LoadTexture("wabbit_alpha.png");
  wabbit_size = (Vector2){wabbit.width, wabbit.height};
  wabbitPos = (Vector2){game_width / 2.0,
                        game_height - PLAYER_SPAWN_BOTTOM_OF_SCREEN_GAP};
}
void Die() {
  wabbitPos = (Vector2){game_width / 2.0,
                        game_height - PLAYER_SPAWN_BOTTOM_OF_SCREEN_GAP};
  hp = max_hp;
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
      Vector2 pos = {wabbitPos.x + wabbit_size.x / 2, wabbitPos.y};
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
  wabbitPos.x = Clamp(wabbitPos.x, 0, game_width - wabbit_size.x);
  wabbitPos.y = Clamp(wabbitPos.y, 0, game_height - wabbit_size.y);

  Rectangle rec = {wabbitPos.x, wabbitPos.y, wabbit_size.x, wabbit_size.y};
  for (int b = 0; b < MAX_BULLETS; b++) {
    if (bullets[b].disabled || bullets[b].friendly) {
      continue;
    }

    if (CheckCollisionCircleRec(bullets[b].position, bulletRadius, rec)) {
      bullets[b].disabled = true;
      hp -= 1;
      if (hp < 1) {
        Die();
      }
    }
  }
}

#endif
