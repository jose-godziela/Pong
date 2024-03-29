#pragma once
#include "raylib.h"

namespace Godziela
{
	const int TOTAL_PLAYERS = 2;
	const int PLAYER1 = 0;
	const int PLAYER2 = 1;
	const int MAX_COLOR = 6;

	extern float posX_player1;
	extern float posX_player2;
	extern float posY_players;
	extern float vel_player;

	struct Player {
		Rectangle rec;
		Vector2 size;
		int score;
		Color color;
		Texture2D texture;
		Image img;
	};
	extern Player players[TOTAL_PLAYERS];

	void init_players();
	void reset_pos_players();

	void set_random_color_player(Player &p);


}