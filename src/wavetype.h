#ifndef WAVETYPE_H
#define WAVETYPE_H

#include <raylib.h>

typedef struct LevelWave {
  char objects[512];
  bool active; // Part of the current set of waves
  bool complete;
} LevelWave;

#endif
