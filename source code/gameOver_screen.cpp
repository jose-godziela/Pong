#include "gameOver_screen.h"

int frames;

void init_frames()
{
	frames = 0;
}

void draw_gameOver()
{
	StopMusicStream(background_music);
	PlayMusicStream(gameOver_music);
	UpdateMusicStream(gameOver_music);
	DrawText("GAME OVER", GetScreenWidth() / 3, GetScreenHeight() / 2.5f, 50, RED);
	frames++;

	if (frames > GAME_OVER_TIME)
	{
		players[PLAYER1].score = 0;
		players[PLAYER2].score = 0;
		game_start = false;
		gameState = MENU;
		StopMusicStream(gameOver_music);
		frames = 0;
	}
}