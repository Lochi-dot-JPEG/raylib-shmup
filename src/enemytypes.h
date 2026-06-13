#ifndef ENEMYTYPES_H
#define ENEMYTYPES_H
#include <stdio.h>
#include <string.h>

typedef struct EnemyType {
  int Hp;
  int Speed;
  int Size;
  int MovePattern;
  int BulletPattern;
  float BulletSpeed;
  float ShootCooldown;
} EnemyType;

const char EnemyTypeKeys[][8] = {
    "spray",
    "shoot",
};
const EnemyType EnemyTypes[] = { // Declare all types
    {
        // spray
        .Hp = 5,
        .Speed = 100,
        .Size = 15,
        .MovePattern = 1,
        .BulletPattern = 1,
        .BulletSpeed = 100,
        .ShootCooldown = 40,
    },
    {
        // shoot
        .Hp = 50,
        .Speed = 50,
        .Size = 40,
        .MovePattern = 1,
        .BulletPattern = 1,
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

#endif
