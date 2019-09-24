#pragma once
#include "libraries.h"
const int CANT_REC = 7;

enum GameType {
	PvP,	//Player vs Player
	PvB,	//Player vs Bot
	BvB		//Bot vs Bot
};

extern GameType gameType;
enum GameState {
	MENU,
	GAME,
	END
};

extern GameState gameState;
extern Vector2 mouse_pos;
extern Rectangle buttons[CANT_REC];
extern Music background_music;
extern Music gameOver_music;
extern Music menu_music;


void draw_menu();
void change_menu_options();