#include "game_over_screen.h"


namespace Godziela
{
	int frames;
	int draw_x;
	int draw_y;
	int winner;
	void init_game_over()
	{
		frames = 0;
		draw_x = (GetScreenWidth() / (7/2));
		draw_y = (GetScreenHeight() / 4);
	}

	void change_screen()
	{
		players[PLAYER1].score = 0;
		players[PLAYER2].score = 0;
		game_start = false;
		gameState = MENU;
		StopMusicStream(gameOver_music);
		frames = 0;
	}

	void draw_game_over()
	{
		if (players[PLAYER1].score > players[PLAYER2].score)
			winner = 0;
		else
			winner = 1;

		StopMusicStream(background_music);
		PlayMusicStream(gameOver_music);
		UpdateMusicStream(gameOver_music);

		DrawText("GAME OVER", draw_x, draw_y, 50, RED);
		DrawText(FormatText("Winner: Player %i", winner + 1), draw_x, draw_y + 80, 30, BLUE);
		DrawText(FormatText("Points: %i", players[winner].score), draw_x, draw_y + 140, 30, BLUE);
		frames++;

		if (frames > game_over_time)
		{
			change_screen();
		}
	}
}