#include "game_over_screen.h"


namespace Godziela
{
	int frames;
	float draw_x;
	float draw_y;

	void init_game_over()
	{
		frames = 0;
		draw_x = (float)(GetScreenWidth() / 3);
		draw_y = (float)(GetScreenWidth() / 2.5f);
	}

	void draw_gameOver()
	{
		StopMusicStream(background_music);
		PlayMusicStream(gameOver_music);
		UpdateMusicStream(gameOver_music);
		DrawText("GAME OVER", (int)draw_x, (int)draw_y, 50, RED);
		frames++;

		if (frames > game_over_time)
		{
			players[PLAYER1].score = 0;
			players[PLAYER2].score = 0;
			game_start = false;
			gameState = MENU;
			StopMusicStream(gameOver_music);
			frames = 0;
		}
	}
}