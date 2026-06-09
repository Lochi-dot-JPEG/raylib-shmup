#ifndef ENEMIES_H
#define ENEMIES_H
#include "bullets.h"
#include "math.h"
#include "raylib.h"
#include "raymath.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct Enemy {
  Vector2 position;
  Vector2 direction;
  int speed;
  int size;
  // int movePattern;
  int hp;
  int Sprite;
  bool disabled;
} Enemy;

#define ENEMY_DEFAULTS {.disabled = false}

#define MAX_ENEMIES 200

Enemy *enemies;

void enm_Init() {
  enemies = (Enemy *)RL_CALLOC(MAX_ENEMIES, sizeof(Enemy));
  for (int i = 0; i < MAX_ENEMIES; i++) {
    enemies[i].disabled = true;
  }
}

void enm_New(Vector2 origin, int hp) {
  int foundIndex = 0;
  // Will override the last bullet if there are no disabled bullets
  for (int e = 0; e < MAX_ENEMIES; e++) {
    if (enemies[e].disabled == true) {
      foundIndex = e;
      break;
    }
  }
  enemies[foundIndex].position = (Vector2){origin.x, origin.y};
  enemies[foundIndex].hp = hp;
  enemies[foundIndex].disabled = false;
  enemies[foundIndex].speed = 200;
  enemies[foundIndex].size = 15;
  enemies[foundIndex].direction = (Vector2){1, 0.5};
}

void enm_Draw() {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    // TODO figure out if using a reference here is more optimal
    Enemy e = enemies[i];
    if (e.disabled) {
      continue;
    }
    DrawCircle((int)e.position.x, (int)e.position.y, e.size, PURPLE);
  }
}

void Collide_Bullets() {
  for (int e = 0; e < MAX_ENEMIES; e++) {
    Enemy *enemy = &enemies[e];
    if (enemy->disabled) {
      continue;
    }
    int hitDistance = bulletRadius + enemy->size;
    int hitDistanceSqr = hitDistance * hitDistance;
    for (int i = 0; i < MAX_BULLETS; i++) {
      Bullet *b = &bullets[i];
      if (b->disabled) {
        continue;
      }
      if (Vector2DistanceSqr(b->position, enemy->position) < hitDistanceSqr) {
        enemy->hp -= 1;
        if (enemy->hp <= 0) {
          enemy->disabled = true;
        }
        b->disabled = true;
      }
    }
  }
}

void enm_Update(float delta) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    Enemy e = enemies[i];
    if (e.disabled) {
      continue;
    }
    enemies[i].position.x += e.direction.x * e.speed * delta;
    enemies[i].position.y += e.direction.y * e.speed * delta;
  }
  Collide_Bullets();
}

#endif
