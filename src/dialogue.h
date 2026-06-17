
#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <raylib.h>

extern bool in_dialogue;

void StartDialogue(char name, char line[512]);
void dlg_Init();

void dlg_Draw();

#endif
