#pragma once
#include "raylib.h"

#include "audio.h"
#include "players.h"
#include "menu_screen.h"
#include "game_screen.h"

namespace Godziela
{
	extern int frames;
	extern int draw_x;
	extern int draw_y;
	extern int winner;
	const int game_over_time = 77000;



	void draw_game_over();
	void init_game_over();
}