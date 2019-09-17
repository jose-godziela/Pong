#ifndef PLAYERS_H
#define PLAYERS_H
#include "libraries.h"
const int TOTAL_PLAYERS = 2;
const int PLAYER1 = 0;
const int PLAYER2 = 1;

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
#endif
