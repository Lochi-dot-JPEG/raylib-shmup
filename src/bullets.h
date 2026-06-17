#ifndef BULLETS_H
#define BULLETS_H

#include "bullettype.h"
#include "raylib.h"

void bul_Init();
void moveBullets(float delta, int winWidth, int winHeight);
void bul_Update(float delta, int winWidth, int winHeight);
Bullet *createBulletAtPoint(Vector2 origin, Vector2 velocity, bool friendly);
void bul_Draw();
void bul_Clear();

#endif
