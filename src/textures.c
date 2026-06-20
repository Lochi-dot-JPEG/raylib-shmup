#include "raylib.h"

Texture2D texture_map;
Vector2 origin_vec = {0, 0};

void tex_Init() { texture_map = LoadTexture("texture_map.png"); }
