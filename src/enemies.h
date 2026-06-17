
#ifndef ENEMIES_H
#define ENEMIES_H
#include "raylib.h"
#include <enemytypes.h>
#include <raymath.h>
#include <windowscale.h>

void enm_Init();

void enm_New(Vector2 origin, char *type);

void enm_Draw();

bool enm_Update(float delta);

void enm_Clear();

#endif
