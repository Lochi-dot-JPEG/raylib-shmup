#ifndef DIALOGUE_C
#define DIALOGUE_C

#include "raylib.h"
#include "raymath.h"
#include "stdio.h"
#include <namemappings.h>
#include <string.h>
#include <windowscale.h>

#define NAME_POS_X 16
#define NAME_POS_Y (GAME_HEIGHT - 128)
#define DIALOGUE_POS_X 16
#define DIALOGUE_POS_Y (GAME_HEIGHT - 104)
Rectangle PortraitPos = {0, GAME_HEIGHT - 128, 128, 128};

bool in_dialogue = false;
char current_name[128];
char current_line[512];
Texture portraits_texture;

void StartDialogue(char name, char line[512]) {
  in_dialogue = true;
  int nameID = 0;
  for (int i = 0; i < NAME_COUNT; i++) {
    if (name_to_index[i] == name) {
      nameID = i;
      break;
    }
  }

  printf("line is %s", line); // Data is broken here
  strcpy(current_name, full_names[nameID]);
  strcpy(current_line, line);
}
void dlg_Init() { portraits_texture = LoadTexture("portraits.png"); }

void dlg_Draw() {
  if (!in_dialogue) {
    return;
  }
  int portrait = 0;
  if (strcmp(current_name, full_names[0]) == 0) {
    portrait = 0;
  } else if (strcmp(current_name, full_names[1]) == 0) {
    portrait = 1;
  }
  Rectangle SourceRect = {0, 128 * portrait, 128, 128};

  DrawTexturePro(portraits_texture, SourceRect, PortraitPos, Vector2Zero(), 0,
                 WHITE);
  DrawText(current_name, NAME_POS_X, NAME_POS_Y, 20, WHITE);
  // TODO wrap text using raylib example
  DrawText(current_line, DIALOGUE_POS_X, DIALOGUE_POS_Y, 10, WHITE);
}
#endif
