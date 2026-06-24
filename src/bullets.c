#include "bullettype.h"
#include "raylib.h"
#include "textures.h"
#include <stdio.h>
#include <stdlib.h>
float bulletSpeed = 200.0f;
#define bulletColor RED;

Bullet *bullets;
int active_bullets = 0;

void bul_Init() {
  bullets = (Bullet *)RL_CALLOC(MAX_BULLETS, sizeof(Bullet));
  for (int i = 0; i < MAX_BULLETS; i++) {
    bullets[i].disabled = true;
  }
}

void moveBullets(float delta, int winWidth, int winHeight) {
  active_bullets = 0;
  for (int i = 0; i < MAX_BULLETS; i++) {
    Bullet b = bullets[i];
    if (!b.disabled) {
      active_bullets++;
      bullets[i].position.x += b.velocity.x * delta;
      bullets[i].position.y += b.velocity.y * delta;
      if (b.position.x < 0 || b.position.x > winWidth || b.position.y < 0 ||
          b.position.y > winHeight) {
        bullets[i].disabled = true;
      }
    }
  }
}

void bul_Update(float delta, int winWidth, int winHeight) {
  moveBullets(delta, winWidth, winHeight);
}

Bullet *createBulletAtPoint(Vector2 origin, Vector2 velocity, bool friendly) {
  int foundIndex = 0;
  // Will override the last bullet if there are no disabled bullets
  for (int b = 0; b < MAX_BULLETS; b++) {
    if (bullets[b].disabled == true) {
      foundIndex = b;
      break;
    }
  }
  bullets[foundIndex].position = origin;
  bullets[foundIndex].velocity.x = velocity.x;
  bullets[foundIndex].velocity.y = velocity.y;
  bullets[foundIndex].color = RED;
  bullets[foundIndex].disabled = false;
  bullets[foundIndex].friendly = friendly;
  if (friendly) {
    bullets[foundIndex].radius = 7;
    bullets[foundIndex].textureSource = (Rectangle){12, 33, 16, 16};
  } else {
    bullets[foundIndex].radius = 5;
    bullets[foundIndex].textureSource = (Rectangle){0, 32, 12, 12};
  }
  return &bullets[foundIndex];
}

void bul_Draw() {
  int drawnBullets = 0;
  // Draw bullets
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullets[i].disabled) {
      continue;
    }
    drawnBullets++;
    Bullet b = bullets[i];
    int pos_radius = b.textureSource.width;
    int half_pos_radius = pos_radius / 2;
    Rectangle pos = {b.position.x, b.position.y, pos_radius, pos_radius};
    Vector2 origin = {half_pos_radius, half_pos_radius};
    DrawTexturePro(texture_map, b.textureSource, pos, origin, 0, WHITE);
    // DrawCircle(pos.x, pos.y, bullets[i].radius, bullets[i].color);
  }
  char str[8];
  snprintf(str, sizeof(str), "%d", drawnBullets);
  DrawText(str, 360 - 95, 50, 20, WHITE);
}

void bul_Clear() {
  for (int i = 0; i < MAX_BULLETS; i++) {
    bullets[i].disabled = true;
  }
}
