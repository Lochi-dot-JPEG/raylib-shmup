#include "bullets.h"
#include "bullettype.h"
#include "math.h"
#include "raylib.h"
#include "raymath.h"
#include <enemytypes.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <windowscale.h>

const EnemyType EnemyA = {1, 1, 30};
typedef struct Enemy {
  Vector2 main_position;
  Vector2 position;
  Vector2 direction;
  int speed;
  int size;
  int movePattern;
  int hp;
  int Sprite;
  int bulletSpeed;
  int shootPattern;
  int shootCooldown;
  int shootTimer;
  bool disabled;
} Enemy;

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
  if (origin.x < GAME_WIDTH / 2.0) {
    enemies[foundIndex].position.x = -50;
  } else {
    enemies[foundIndex].position.x = 50 + GAME_WIDTH;
  }

  EnemyType thisType = GetEnemyType(type);
  enemies[foundIndex].hp = thisType.Hp;
  enemies[foundIndex].disabled = false;
  enemies[foundIndex].speed = thisType.Speed;
  enemies[foundIndex].size = thisType.Size;
  enemies[foundIndex].shootPattern = thisType.ShootPattern;
  enemies[foundIndex].shootCooldown = thisType.ShootCooldown;
  enemies[foundIndex].shootTimer = thisType.ShootCooldown;
  enemies[foundIndex].bulletSpeed = thisType.BulletSpeed;
  enemies[foundIndex].direction = (Vector2){1, 0.5};
}

void CreateEnemyBullets(Enemy enemy) {

  // printf("shoot pattern is %d\n", enemy.shootPattern);
  switch (enemy.shootPattern) {
  case 0: // alternating spray
    Vector2 down_angle = {0, 1};
#define ALT_SPRAY_SPREAD (1 / 18.0 * PI)
    Vector2 angles[3] = {{0, 1},
                         Vector2Rotate(down_angle, ALT_SPRAY_SPREAD),
                         Vector2Rotate(down_angle, -ALT_SPRAY_SPREAD)};
    for (int i = 0; i < 3; i++) {
      Vector2 bulVelo = {angles[i].x * enemy.bulletSpeed,
                         angles[i].y * enemy.bulletSpeed};
      createBulletAtPoint(enemy.position, bulVelo, false);
    }

    return;
  case 1: // slow forward shooting
    Vector2 bulVelo = {0, enemy.bulletSpeed};
    bulVelo = Vector2Rotate(bulVelo, DEG2RAD * GetRandomValue(-10, 10));
    Bullet *b = createBulletAtPoint(enemy.position, bulVelo, false);
  case 2:
    return;
  case 3:
    return;
  case 4:
    return;
  default:
    printf("Couldnt find bullet pattern %d", enemy.shootPattern);
    return;
  }
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
    bool col = CheckCollisionCircles(b->position, b->radius, enemy->position,
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
      CreateEnemyBullets(*e);
    }
  }
  return any_enemies;
}

void enm_Clear() {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    enemies[i].disabled = true;
  }
}
