// Frames until a new bullet is made
#include "player.h"
#include "bullettype.h"
#include "colors.h"
#include "textures.h"
#include <bullets.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <waves.h>
#include <windowscale.h>

#define PLAYER_SPAWN_BOTTOM_OF_SCREEN_GAP 50
#define PLAYER_BULLET_SPEED 600

static int shooting = 0;
bool can_shoot = true;
#define MAX_HP 15
static int hp = MAX_HP;
int combo = 0;
Rectangle texture_location = {0, 0, 14, 24};
Vector2 origin;
Color focusHitboxColor;

Vector2 wabbit_size;

bool focus_mode = false;
Vector2 wabbitPos = {0, 0};
int wabbitSpeed = 200;
Vector2 bulletDirections[3] = {{0.070, -0.997}, {0, -1}, {-0.070, -0.997}};
Vector2 focusBulletDirections[3] = {{0.035, -0.999}, {0, -1}, {-0.035, -0.999}};
float bulletOffsets[3] = {8, 0, -8};

int GetComboLevel() { return combo / COMBO_TIER_SIZE; }

void ply_Init() {
  wabbitPos = (Vector2){GAME_WIDTH / 2.0,
                        GAME_HEIGHT - PLAYER_SPAWN_BOTTOM_OF_SCREEN_GAP};

  focusHitboxColor = GetColor(0xd3a6a6ab);
  wabbit_size = (Vector2){texture_location.width, texture_location.height};
  origin = (Vector2){texture_location.width / 2, texture_location.height / 2};
}
void Die() {
  wvs_Reload_Level();
  wabbitPos = (Vector2){GAME_WIDTH / 2.0,
                        GAME_HEIGHT - PLAYER_SPAWN_BOTTOM_OF_SCREEN_GAP};
  hp = MAX_HP;
}

void createPlayerBullets(Vector2 playerPos, float delta, bool focused) {
  switch (GetComboLevel()) {
  case 0:
    Vector2 dir0 = {0, -PLAYER_BULLET_SPEED};
    createBulletAtPoint(playerPos, dir0, true);
    break;

    break;
  case 1:
    Vector2 pos1a = playerPos;
    Vector2 pos1b = playerPos;
    pos1a.x += 10;
    pos1b.x -= 10;

    Vector2 dir1 = {0, -PLAYER_BULLET_SPEED};
    createBulletAtPoint(pos1a, dir1, true);
    createBulletAtPoint(pos1b, dir1, true);
    break;
  default:
    for (int i = 0; i < 3; i++) {

      Vector2 pos = playerPos;
      pos.x += bulletOffsets[i];

      Vector2 dir;
      if (focused) {
        dir = (Vector2){focusBulletDirections[i].x * PLAYER_BULLET_SPEED,
                        focusBulletDirections[i].y * PLAYER_BULLET_SPEED};
      } else {
        dir = (Vector2){bulletDirections[i].x * PLAYER_BULLET_SPEED,
                        bulletDirections[i].y * PLAYER_BULLET_SPEED};
      }
      createBulletAtPoint(pos, dir, true);
    }
    break;
  }
}

void ply_Draw() {
  Rectangle location_rec = {(int)wabbitPos.x, (int)wabbitPos.y, wabbit_size.x,
                            wabbit_size.y};
  DrawTexturePro(texture_map, texture_location, location_rec, origin, 0, WHITE);
  if (focus_mode) {
    DrawCircleLinesV(wabbitPos, 5, focusHitboxColor);
  }

  char str[8];
  snprintf(str, sizeof(str), "%d", hp);
  DrawText(str, 360 - 95, 80, 20, WHITE);
}

void ply_Update() {
  focus_mode = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_K);

  if (can_shoot) {
    if (IsKeyDown(KEY_J) || IsKeyDown(KEY_Z)) {
      if (shooting == 5) {
        Vector2 pos = {wabbitPos.x, wabbitPos.y};
        createPlayerBullets(pos, GetFrameTime(), focus_mode);
        shooting = 0;
      }
      shooting++;
    } else {
      shooting = 5;
    }
  }

  float current_speed = focus_mode ? wabbitSpeed / 2 : wabbitSpeed;

  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
    wabbitPos.x += current_speed * GetFrameTime();
  }
  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
    wabbitPos.x -= current_speed * GetFrameTime();
  }
  if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
    wabbitPos.y -= current_speed * GetFrameTime();
  }
  if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
    wabbitPos.y += current_speed * GetFrameTime();
  }
  wabbitPos.x = Clamp(wabbitPos.x, 0, GAME_WIDTH - wabbit_size.x);
  wabbitPos.y = Clamp(wabbitPos.y, 0, GAME_HEIGHT - wabbit_size.y);

  Rectangle rec = {wabbitPos.x, wabbitPos.y, wabbit_size.x, wabbit_size.y};
  for (int b = 0; b < MAX_BULLETS; b++) {
    if (bullets[b].disabled || bullets[b].friendly) {
      continue;
    }

    if (CheckCollisionCircles(bullets[b].position, bullets[b].radius, wabbitPos,
                              5)) {
      bullets[b].disabled = true;
      combo = 0;
      hp -= 1;
      if (hp < 1) {
        Die();
      }
    }
  }
}

void ply_Unload() {}

void ply_DrawUI() {
  for (int i = 0; i < hp; i++) {
    DrawRectangle(8, 8 + i * 8, 16, 4, background_color);
  }

  if (combo > 0) {
    char text[8] = "";
    sprintf(text, "%dx", combo);
    char leveltext[8] = "";
    sprintf(leveltext, "%dx", GetComboLevel());

    DrawText("Combo", GAME_WIDTH - 48, 8, 16, text_color);
    DrawText(text, GAME_WIDTH - 48, 32, 16, text_color);
    DrawText("Power", GAME_WIDTH - 48, 48, 16, text_color);
    DrawText(leveltext, GAME_WIDTH - 48, 64, 16, text_color);
  }
}
