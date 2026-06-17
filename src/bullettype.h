#ifndef BULLETTYPE
#define BULLETTYPE

#include "raylib.h"

#define BULLET_RADIUS 5 // TODO remove this and define bullet types
#define MAX_BULLETS 10000
typedef struct Bullet {
  Vector2 position;
  Vector2 velocity;
  Color color;
  bool disabled;
  bool friendly;
  int damage; /* TODO implement*/
  int radius;
} Bullet;

extern Bullet *bullets;
extern int active_bullets;

#endif
