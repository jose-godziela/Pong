#include "Players.h"

namespace Godziela
{
	float posX_player1 = 0;
	float posX_player2 = 0;
	float posY_players = 0;
	float vel_player = 400.0f;
	Player players[TOTAL_PLAYERS];

	void init_players()
	{
		posX_player1 = (float)(GetScreenWidth() / 15);
		posX_player2 = (float)(GetScreenWidth() - (GetScreenWidth() / 12));
		posY_players = (float)(GetScreenHeight() / 2);
		//Players Creation
		for (int i = 0; i < TOTAL_PLAYERS; i++) {
			players[i].score = 0;
			players[i].size.x = 10.0f;
			players[i].size.y = 50.0f;

			players[i].rec.x = posX_player1;
			players[i].rec.y = posY_players;

			players[i].rec.width = players[i].size.x;
			players[i].rec.height = players[i].size.y;
			players[i].color = BLUE;
			//Player Texture
			players[i].img = LoadImage("resources/players.png");
			ImageRotateCW(&players[i].img);
			ImageResize(&players[i].img, (int)players[i].size.x, (int)players[i].size.y);
			players[i].texture = LoadTextureFromImage(players[i].img);
			UnloadImage(players[i].img);
			if (i == PLAYER2)
			{
				//Player 2 X position and base color
				players[PLAYER2].rec.x = posX_player2;
				players[PLAYER2].color = RED;

			}

		}
	}

	void reset_pos_players()
	{
		players[PLAYER1].rec.x = posX_player1;
		players[PLAYER1].rec.y = posY_players;
		players[PLAYER2].rec.x = posX_player2;
		players[PLAYER2].rec.y = posY_players;
	}

	void set_random_color_player(Player &p) {
		switch (GetRandomValue(1, MAX_COLOR))
		{
		case 1: {
			p.color = RED;
			break;
		}
		case 2: {
			p.color = BLUE;
			break;
		}
		case 3: {
			p.color = YELLOW;
			break;
		}
		case 4: {
			p.color = GREEN;
			break;
		}
		case 5: {
			p.color = GRAY;
			break;
		}
		case 6: {
			p.color = WHITE;
			break;
		}
		}
	}
}
