#ifndef BULLETTYPE
#define BULLETTYPE

#include "raylib.h"

#define MAX_BULLETS 10000
typedef struct Bullet {
  Vector2 position;
  Vector2 velocity;
  Color color;
  bool disabled;
  bool friendly;
  int damage; /* TODO implement*/
  int radius;
  Rectangle textureSource;
} Bullet;

extern Bullet *bullets;
extern int active_bullets;

#endif
