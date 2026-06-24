#ifndef WAVES_H
#define WAVES_H

#include "wavetype.h"
#include <raylib.h>

extern bool done_looping;
void wvs_Init();
void wvs_NextWave();
void wvs_Reload_Level();
void wvs_Update(bool has_active_enemies);
void wvs_LoadLevel(char *level_name);
void LoadLevelWave(LevelWave newWave);

#endif
