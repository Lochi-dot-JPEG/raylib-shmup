#include "bullets.h"
#include "bullettype.h"
#include "math.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "sounds.h"
#include "textures.h"
#include <enemytypes.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  Rectangle texture_rect;
  float time_offset;
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
  if (strcmp(type, "dart") != 0) {
    if (origin.x < GAME_WIDTH / 2.0) {
      enemies[foundIndex].position.x = -50;
    } else {
      enemies[foundIndex].position.x = 50 + GAME_WIDTH;
    }
  } else {
    if (origin.x < GAME_WIDTH / 2.0) {
      enemies[foundIndex].position.x = origin.x - 20;
    } else {
      enemies[foundIndex].position.x = origin.x + 20;
    }
  }

  EnemyType thisType = GetEnemyType(type);
  enemies[foundIndex].hp = thisType.Hp;
  enemies[foundIndex].disabled = false;
  enemies[foundIndex].speed = thisType.Speed;
  enemies[foundIndex].size = thisType.Size;
  enemies[foundIndex].shootPattern = thisType.ShootPattern;
  enemies[foundIndex].shootCooldown = thisType.ShootCooldown;
  enemies[foundIndex].shootTimer =
      (float)GetRandomValue(0, thisType.ShootCooldown);
  enemies[foundIndex].bulletSpeed = thisType.BulletSpeed;
  enemies[foundIndex].movePattern = thisType.MovePattern;
  enemies[foundIndex].direction = (Vector2){1, 0.5};
  enemies[foundIndex].texture_rect = thisType.TextureLocation;
  enemies[foundIndex].time_offset = (float)GetRandomValue(0, 4000) * 0.01;
}

void CreateEnemyBullets(Enemy enemy) {
  PlaySound(snd_enemy_shoot);

  switch (enemy.shootPattern) {
  case 0: // alternating spray
    Vector2 down_angle = {0, 1};
#define ALT_SPRAY_SPREAD (1 / 12.0 * PI)
    Vector2 angles[5] = {{0, 1},
                         Vector2Rotate(down_angle, ALT_SPRAY_SPREAD * 2),
                         Vector2Rotate(down_angle, -ALT_SPRAY_SPREAD * 2),
                         Vector2Rotate(down_angle, ALT_SPRAY_SPREAD),
                         Vector2Rotate(down_angle, -ALT_SPRAY_SPREAD)};
    for (int i = 0; i < 5; i++) {
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
    Enemy e = enemies[i];
    if (e.disabled) {
      continue;
    }
    Rectangle location_rec = {round(e.position.x), round(e.position.y),
                              e.texture_rect.width, e.texture_rect.height};

    Vector2 origin = {round(e.texture_rect.width / 2.0),
                      round(e.texture_rect.height / 2.0)};

    // DrawCircle((int)e.position.x, (int)e.position.y, e.size, PURPLE);
    DrawTexturePro(texture_map, e.texture_rect, location_rec, origin, 0, WHITE);
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
        PlaySound(snd_kill);
      } else {
        PlaySound(snd_hurt);
      }
      b->disabled = true;
      combo++;
    }
  }
}

bool enm_Update(float delta) {
  bool any_enemies = false;
  float game_time = GetTime();
  for (int i = 0; i < MAX_ENEMIES; i++) {
    Enemy *e = &enemies[i];
    if (e->disabled) {
      continue;
    }
    any_enemies = true;
    float enemy_offset_time = game_time + e->time_offset;

    Vector2 target_position = e->main_position;
    switch (e->movePattern) {
    case 0:
      break;
    case 1:
      target_position.x += sinf(enemy_offset_time * 4) * 24;
      enemies[i].position =
          Vector2MoveTowards(e->position, target_position, e->speed * delta);
      break;
    case 2:
      target_position.x += sinf(enemy_offset_time * 2) * 24;
      target_position.y += cosf(enemy_offset_time * 2) * 24;
      enemies[i].position =
          Vector2MoveTowards(e->position, target_position, e->speed * delta);
      break;
    case 3:
      e->main_position.y +=
          delta * e->speed * (1 + 0.2 * sinf(enemy_offset_time * 3));
      e->position.y +=
          delta * e->speed * (1 + 0.2 * sinf(enemy_offset_time * 3));
      if (e->position.y > GAME_HEIGHT - 16 && e->speed > 0) {
        e->speed = -e->speed;
      }
      if (e->position.y < 16 && e->speed < 0) {
        e->speed = -e->speed;
      }
      break;
    }
    if (e->position.y > GAME_HEIGHT + 32) {
      e->disabled = true;
    }

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
