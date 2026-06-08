#include "raylib.h"

typedef struct Bullet {
  Vector2 position;
  Vector2 velocity;
  Color color;
  bool disabled;
} Bullet;

#define MAX_BULLETS 10000

void moveBullets(Bullet *bullets, int bulletCount, float delta, int winWidth,
                 int winHeight) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    Bullet b = bullets[i];
    if (!b.disabled) {
      bullets[i].position.x += b.velocity.x * delta;
      bullets[i].position.y += b.velocity.y * delta;
      if (b.position.x < 0 || b.position.x > winWidth || b.position.y < 0 ||
          b.position.y > winHeight) {
        bullets[i].disabled = true;
      }
    }
  }
}

void createBulletAtPoint(Vector2 origin, Vector2 velocity, Bullet *bullets,
                         float delta) {
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
}
