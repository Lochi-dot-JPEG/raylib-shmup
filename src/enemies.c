#ifndef ENEMIES_C
#define ENEMIES_C
#include "bullets.h"
#include "math.h"
#include "raylib.h"
#include "raymath.h"
#include <enemytypes.h>
#include <raymath.h>
#include <stdio.h>
#include <windowscale.h>

const EnemyType EnemyA = {1, 1, 30};
typedef struct Enemy {
  Vector2 main_position;
  Vector2 position;
  Vector2 direction;
  int speed;
  int bulletSpeed;
  int size;
  // int movePattern;
  int hp;
  int Sprite;
  int shootCooldown;
  int shootTimer;
  bool disabled;
} Enemy;

#define ENEMY_DEFAULTS {.disabled = false}

#define MAX_ENEMIES 100

Enemy *enemies;

void enm_Init() {
  enemies = (Enemy *)RL_CALLOC(MAX_ENEMIES, sizeof(Enemy));
  for (int i = 0; i < MAX_ENEMIES; i++) {
    enemies[i].disabled = true;
  }
}

void enm_New(Vector2 origin, char *type) {
  int foundIndex = 0;
  // Will override the last bullet if there are no disabled bullets
  for (int e = 0; e < MAX_ENEMIES; e++) {
    if (enemies[e].disabled == true) {
      foundIndex = e;
      break;
    }
  }
  enemies[foundIndex].main_position = (Vector2){origin.x, origin.y};
  enemies[foundIndex].main_position = (Vector2){origin.x, origin.y};
  enemies[foundIndex].position.y = -50;
  if (origin.x < game_width / 2.0) {
    enemies[foundIndex].position.x = -50;
  } else {
    enemies[foundIndex].position.x = 50 + game_width;
  }

  EnemyType thisType = GetEnemyType(type);
  enemies[foundIndex].hp = thisType.Hp;
  enemies[foundIndex].disabled = false;
  enemies[foundIndex].speed = thisType.Speed;
  enemies[foundIndex].size = thisType.Size;
  enemies[foundIndex].shootCooldown = thisType.ShootCooldown;
  enemies[foundIndex].shootTimer = thisType.ShootCooldown;
  enemies[foundIndex].bulletSpeed = thisType.BulletSpeed;
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

void Collide_Bullets(Enemy *enemy) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    Bullet *b = &bullets[i];
    if (b->disabled || !(b->friendly)) {
      continue;
    }
    bool col = CheckCollisionCircles(b->position, bulletRadius, enemy->position,
                                     enemy->size);
    if (col) {
      enemy->hp -= 1;
      if (enemy->hp <= 0) {
        enemy->disabled = true;
      }
      b->disabled = true;
    }
  }
}

bool enm_Update(float delta) {
  bool any_enemies = false;
  for (int i = 0; i < MAX_ENEMIES; i++) {
    Enemy *e = &enemies[i];
    if (e->disabled) {
      continue;
    }
    any_enemies = true;
    enemies[i].position =
        Vector2MoveTowards(e->position, e->main_position, e->speed * delta);
    // printf("Enemy pos = %f, %f\n", e->position.x, e->position.y);
    Collide_Bullets(e);
    e->shootTimer--;
    if (e->shootTimer <= 0) {
      e->shootTimer = e->shootCooldown;
      Vector2 bulVelo = {0, e->bulletSpeed};
      bulVelo = Vector2Rotate(bulVelo, DEG2RAD * GetRandomValue(-10, 10));

      Bullet *b = createBulletAtPoint(e->position, bulVelo, false);
    }
  }
  return any_enemies;
}

#endif
