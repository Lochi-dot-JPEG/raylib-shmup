
#include "enemytypes.h"
#include <stdio.h>
#include <string.h>
const char EnemyTypeKeys[][8] = {
    "shoot",
    "spray",
};
const EnemyType EnemyTypes[] = { // Declare all types
    {
        // shoot
        .Hp = 15,
        .Speed = 200,
        .Size = 15,
        .MovePattern = 1,
        .ShootPattern = 1,
        .BulletSpeed = 100,
        .ShootCooldown = 40,
    },
    {
        // spray
        .Hp = 50,
        .Speed = 100,
        .Size = 40,
        .MovePattern = 1,
        .ShootPattern = 0,
        .BulletSpeed = 100,
        .ShootCooldown = 20,
    }};
const int EnemyTypeSize = sizeof(EnemyTypeKeys) / sizeof(EnemyTypeKeys[0]);

EnemyType GetEnemyType(char *type) {
  for (int i = 0; i < EnemyTypeSize; i++) {
    if (strcmp(EnemyTypeKeys[i], type) == 0) {
      return EnemyTypes[i];
    }
  }
  printf("Couldn't find type %s, using %s", type, EnemyTypeKeys[0]);
  return EnemyTypes[0];
}
