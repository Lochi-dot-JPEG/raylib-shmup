#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "raylib.h"

extern float bgScroll;
extern bool scroll_background;

void bkg_Init();
void bkg_Draw(float delta);
void bkg_Unload();

#endif
