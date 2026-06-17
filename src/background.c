#include <raylib.h>
#include <windowscale.h>

#include "background.h"
#define BACKGROUND_SPEED 150

Texture2D background;
float bgScroll = 0;
bool scroll_background = true;

void bkg_Init() { background = LoadTexture("background.png"); }

void bkg_Draw(float delta) {
  if (scroll_background) {
    bgScroll += delta * BACKGROUND_SPEED;
  }
  int bgOffset = (int)(bgScroll) % background.height;
  DrawTexture(background, 0, bgOffset, WHITE);
  DrawTexture(background, 0, bgOffset - background.height, WHITE);
}
void bkg_Unload() { UnloadTexture(background); }
