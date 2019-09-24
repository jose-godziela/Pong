#pragma once
#include "raylib.h"
#include "players.h"
#include "ball.h"
#include "menu_screen.h"
#include "game_manager.h"

const Vector2 speedY = { 100, 500 };
const float speed_up = 35.0f;
const int score_max = 5;
const int MOVEMENT = 22;

extern bool game_start;

void game_update();
void draw_game();