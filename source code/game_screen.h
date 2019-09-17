#pragma once
#include "libraries.h"

const Vector2 speedY = { 5, 10 };
const float speed_up = 0.5f;
const int score_max = 5;
const int MOVEMENT = 22;

extern bool game_start;

void game_update();
void draw_game();