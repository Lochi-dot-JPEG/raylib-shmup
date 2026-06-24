
#ifndef PLAYER_H
#define PLAYER_H
// Frames until a new bullet is made
#include "bullettype.h"
#include <bullets.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <waves.h>
#include <windowscale.h>

#define COMBO_TIER_SIZE 50

extern int combo;
extern bool can_shoot;

void ply_Init();
void ply_Draw();
void ply_Update();
void ply_Unload();
void ply_DrawUI();
#endif
