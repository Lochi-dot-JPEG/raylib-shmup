#include "bullets.h"
#include "raylib.h"
#include "wavetype.h"
#include <background.h>
#include <dialogue.h>
#include <enemies.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE1 "spray";
#define MAX_WAVES 512

char currentLevelName[128];
LevelWave loaded_waves[MAX_WAVES];

void LoadLevelWave(LevelWave newWave) {
  int objectCount = 0; // Is set by the TextSplit function
  char **objects = TextSplit(newWave.objects, ',', &objectCount);
  char objectCopies[64][256];

  for (int i = 0; i < objectCount; i++) {
    strcpy(objectCopies[i], objects[i]);
  }

  printf("loads level wave \n");
  printf("object count is %i\n", objectCount);

  // Loop through all objects
  for (int i = 0; i < objectCount; i++) {

    // Copy object string
    char objectCopy[256];
    strcpy(objectCopy, objectCopies[i]);

    // Get properties for the object
    int propertyCount = 0; // Is set by the TextSplit function
    char **objectProperties = TextSplit(objectCopy, ' ', &propertyCount);
    if (propertyCount < 3) {
      if (propertyCount == 1) {
        if (strcmp("scrollstop", objectProperties[0]) == 0) {
          scroll_background = false;
          printf("scrollstop");
          return;
        }
        if (strcmp("scrollstart", objectProperties[0]) == 0) {
          scroll_background = true;
          printf("scrollstart");
          return;
        }
      }
      continue;
    }

    // Store properties
    char *newType = objectProperties[0];
    char *param1 = objectProperties[1];
    char *param2 = objectProperties[2];
    Vector2 newPos = {atoi(param1), atoi(param2)};

    if (strcmp(newType, "spray") == 0) {
      printf("Creating a %s\n", newType);
      enm_New(newPos, "spray");
    } else if (strcmp(newType, "shoot") == 0) {
      printf("Creating a shoot %s\n", newType);
      enm_New(newPos, "shoot");
    } else if (strcmp(newType, "say") == 0) {
      printf("object copy is %s\n", objectCopy); // Data is broken here
      char **quotationSplit = TextSplit(objectCopy, '"', &propertyCount);
      StartDialogue(param1[0], quotationSplit[1]);
    } else {
      printf("Couldn't determine type %s\n", newType);
    }
  }
}

void wvs_LoadLevel(char *level_name) {
  scroll_background = true;
  strcpy(currentLevelName, level_name);
  bul_Clear();
  enm_Clear();

  char *level_data = LoadFileText(level_name);
  printf("level data is \n %s", level_data);
  int line_count;
  if (level_data == NULL) {
    return;
  }
  printf("line count %d", line_count);

  char **lines = TextSplit(level_data, '\n', &line_count);

  char copied_lines[line_count][512];
  for (int i = 0; i < line_count; i++) {
    strcpy(copied_lines[i], lines[i]);
    printf("postcopied line %s\n", copied_lines[i]);
  }
  for (int i = 0; i < MAX_WAVES; i++) {
    if (i < line_count) {
      strcpy(loaded_waves[i].objects, copied_lines[i]);
    }
    loaded_waves[i].active = i < line_count;
  }

  // It shows empty for all of these
  for (int i = 0; i < MAX_WAVES; i++) {
    if (i < line_count) {
    }
  }

  LoadLevelWave(loaded_waves[0]);
  UnloadFileText(level_data);
}

// TODO
void UnloadLevel(char *level_text) { UnloadFileText(level_text); }

void wvs_NextWave() {
  int current_wave;
  int found_wave = false;
  for (current_wave = 0; current_wave < MAX_WAVES; current_wave++) {
    if (!loaded_waves[current_wave].complete) {
      break;
    }
    if (!loaded_waves[current_wave].active) {
      printf("waves done\n");
      return;
    }
  }
  loaded_waves[current_wave].complete = true;
  current_wave++;

  if (strstr(loaded_waves[current_wave].objects, "say")) {
    if (active_bullets == 0) {
      LoadLevelWave(loaded_waves[current_wave]);
    } else {
      // Revert to previous wave
      current_wave--;
      loaded_waves[current_wave].complete = false;
    }
  } else {
    LoadLevelWave(loaded_waves[current_wave]);
  }
}

void wvs_Init() { wvs_LoadLevel("1.txt"); }

void wvs_Reload_Level() { wvs_LoadLevel(currentLevelName); }

void wvs_Update(bool has_active_enemies) {
  if (in_dialogue && IsKeyPressed(KEY_ENTER)) {
    in_dialogue = false;
  }
  if (!has_active_enemies && !in_dialogue) {
    wvs_NextWave();
  }
}
