#pragma once
#include "raylib.h"

#include "players.h"
#include "ball.h"
#include "menu_screen.h"
#include "game_manager.h"

namespace Godziela
{
	const Vector2 speedY = { 200, 500 };
	const float speed_up = 35.0f;
	const int score_max = 5;
	const int MOVEMENT = 22;

	extern bool game_start;
	extern float foo;

	void game_update();
	void draw_game();
	void init_game_screen();
}