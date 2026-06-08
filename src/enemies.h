#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct Enemy {
  Vector2 position;
  Vector2 direction;
  int speed;
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
  enemies[foundIndex].direction = (Vector2){1, 0.5};
}

void enm_Draw() {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    Enemy e = enemies[i];
    if (e.disabled) {
      continue;
    }
    DrawCircle((int)e.position.x, (int)e.position.y, 15, PURPLE);
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
}
