
#include "raylib.h"

Sound snd_enemy_shoot;
Sound snd_player_shoot;
Sound snd_say_f;
Sound snd_say_m;
Sound snd_hurt;
Sound snd_kill;
Sound snd_ping;
Sound snd_power_up;
Sound snd_select;
Sound snd_shoot;

void snd_Init() {
  snd_enemy_shoot = LoadSound("sounds/enemy-shoot.wav");
  snd_say_f = LoadSound("sounds/fairy.wav");
  snd_say_m = LoadSound("sounds/guy.wav");
  snd_hurt = LoadSound("sounds/hurt.wav");
  snd_kill = LoadSound("sounds/kill.wav");
  snd_ping = LoadSound("sounds/ping.wav");
  snd_power_up = LoadSound("sounds/power-up.wav");
  snd_select = LoadSound("sounds/select.wav");
  snd_player_shoot = LoadSound("sounds/shoot.wav");
}
