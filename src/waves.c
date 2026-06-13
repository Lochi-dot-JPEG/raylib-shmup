#ifndef WAVES_C
#define WAVES_C

#include "bullets.h"
#include "raylib.h"
#include <enemies.c>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define TYPE1 "spray";

typedef struct LevelWave {
  char objects[512];
  bool active; // Part of the current set of waves
  bool complete;
} LevelWave;

#define MAX_WAVES 256

char currentLevelName[128];
LevelWave loaded_waves[MAX_WAVES];

// const char wave_items[512] = "spray 100 50,shoot 250 80";

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))

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
      continue;
    }

    // Store properties
    char *newType = objectProperties[0];
    int newPosX = atoi(objectProperties[1]);
    int newPosY = atoi(objectProperties[2]);
    Vector2 newPos = {newPosX, newPosY};

    if (strcmp(newType, "spray") == 0) {
      printf("Creating a %s\n", newType);
      enm_New(newPos, "spray");
    } else if (strcmp(newType, "shoot") == 0) {
      printf("Creating a shoot %s\n", newType);
      enm_New(newPos, "shoot");
    } else {
      printf("Couldn't determine type %s\n", newType);
    }
  }
  printf("\n");
}

// void LoadLevel(char filename[]) { LoadLevelWave(testwave); }
void LoadLevel(char *level_name) {
  strcpy(currentLevelName, level_name);
  bul_Clear();
  enm_Clear();

  char *level_data = LoadFileText(level_name);
  int line_count;
  if (level_data == NULL) {
    return;
  }

  char **lines = TextSplit(level_data, '\n', &line_count);

  char copied_lines[line_count][512];
  for (int i = 0; i < line_count; i++) {
    strcpy(copied_lines[i], lines[i]);
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
  LoadLevelWave(loaded_waves[current_wave]);
}

void wvs_Init() { LoadLevel("testlevel.txt"); }

void wvs_Reload_Level() { LoadLevel(currentLevelName); }

void wvs_Update(bool has_active_enemies) {
  // TODO accomodate for dialogue waves here
  if (!has_active_enemies) {
    wvs_NextWave();
  }
}
#endif
