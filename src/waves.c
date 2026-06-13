#ifndef WAVES_C
#define WAVES_C

#include "raylib.h"
#include <enemies.c>
#include <stdio.h>
#include <string.h>

#define TYPE1 "spray";

typedef struct LevelWave {
  const char *objects;
  int real;
} LevelWave;

const char wave_items[] = "spray 100 50,spray 150 80";

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))

const LevelWave testwave = {wave_items};

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
    int hp = 10; // TODO change based on type using a lookup

    if (strcmp(newType, "spray") == 0) {
      printf("Creating a %s\n", newType);
      enm_New(newPos, hp);
    } else if (strcmp(newType, "shoot") == 0) {
      printf("Creating a shoot %s\n", newType);
      enm_New(newPos, hp);
    } else {
      printf("Couldn't determine type %s\n", newType);
    }
  }
  printf("\n");
}

// void LoadLevel(char filename[]) { LoadLevelWave(testwave); }
void LoadLevel() {

  printf("loads level \n");
  LoadLevelWave(testwave);
}

void wvs_Update() {}
void wvs_NextWave() {}
void wvs_Init() { LoadLevel(); }

#endif
