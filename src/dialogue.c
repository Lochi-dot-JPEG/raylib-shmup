#ifndef DIALOGUE_C
#define DIALOGUE_C

#include "raylib.h"
#include "raymath.h"
#include <string.h>
#include <windowscale.h>

#define NAME_POS_X 16
#define NAME_POS_Y (GAME_HEIGHT - 128)
#define DIALOGUE_POS_X 16
#define DIALOGUE_POS_Y (GAME_HEIGHT - 104)
Rectangle PortraitPos = {0, GAME_HEIGHT - 256, 256, 256};

bool in_dialogue = false;
char current_name[128];
char current_line[512];
Texture portraits_texture;

void StartDialogue(char name[128], char line[512]) {
  in_dialogue = true;
  strcpy(current_name, name);
  strcpy(current_line, line);
}
void dlg_Init() { portraits_texture = LoadTexture("portraits.png"); }

void dlg_Draw() {
  if (!in_dialogue) {
    return;
  }
  int portrait = 0;
  if (strcmp(current_name, "a")) {
    portrait = 0;
  }
  Rectangle SourceRect = {0, 128 * portrait, 128, 128};

  DrawTexturePro(portraits_texture, SourceRect, PortraitPos, Vector2Zero(), 0,
                 WHITE);
  DrawText(current_name, NAME_POS_X, NAME_POS_Y, 15, WHITE);
  // TODO wrap text using raylib example
  DrawText(current_line, DIALOGUE_POS_X, DIALOGUE_POS_Y, 12, WHITE);
}
#endif
