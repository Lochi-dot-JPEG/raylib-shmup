#ifndef ENEMYTYPES_H
#define ENEMYTYPES_H

typedef struct EnemyType {
  int Hp;
  int Speed;
  int Size;
  int MovePattern;
  int ShootPattern; // See CreateEnemyBullets for types
  float BulletSpeed;
  float ShootCooldown;
} EnemyType;
extern const char EnemyTypeKeys[][8];
extern const EnemyType EnemyTypes[];
extern const int EnemyTypeSize;

EnemyType GetEnemyType(char *type);

#endif
