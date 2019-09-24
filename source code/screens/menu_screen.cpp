#include "menu_screen.h"

namespace Godziela
{
	GameType gameType;
	GameState gameState;
	Vector2 mouse_pos = { 0,0 };
	Rectangle buttons[CANT_REC];
	Music menu_music;

	void start()
	{
		StopMusicStream(background_music);
		StopMusicStream(gameOver_music);
	}

	void draw_menu()
	{
		DrawText("Normal Pong", GetScreenWidth() / 3, 10, 40, RAYWHITE);
		DrawText("GameMode:", GetScreenWidth() / 3, GetScreenHeight() / 2 - 70, 20, RAYWHITE);
		//Shows the game type on screen
		switch (gameType)
		{
		case PvP: {
			DrawText("PvP", GetScreenWidth() / 2 + 75, GetScreenHeight() / 2 - 70, 20, YELLOW);
			break;
		}
		case PvB: {
			DrawText("PvB", GetScreenWidth() / 2 + 75, GetScreenHeight() / 2 - 70, 20, RED);
			break;
		};
		case BvB: {
			DrawText("BvB", GetScreenWidth() / 2 + 75, GetScreenHeight() / 2 - 70, 20, BLUE);
			break;
		}
		}
		DrawText("Start the game", GetScreenWidth() / 3, GetScreenHeight() / 2 + 90, 20, RAYWHITE);
		DrawText("Change Gamemode", GetScreenWidth() / 3, GetScreenHeight() / 2 - 90, 20, RAYWHITE);

		DrawText(FormatText("Ball Speed: %f", ball.ball_speed_init.x), GetScreenWidth() / 3, GetScreenHeight() / 2 - 45, 18, GREEN);
		DrawText("Add Speed", GetScreenWidth() / 3, GetScreenHeight() / 2, 20, RAYWHITE);
		DrawText("Substract Speed", GetScreenWidth() / 3, GetScreenHeight() / 2 + 45, 20, RAYWHITE);

		DrawText("Change player colors:", GetScreenWidth() / 15, GetScreenHeight() / 7, 15, RED);
		DrawText("J1: X", GetScreenWidth() / 14, GetScreenHeight() / 4, 18, players[PLAYER1].color);
		DrawText("J2: Z", GetScreenWidth() / 14, GetScreenHeight() / 3, 18, players[PLAYER2].color);

	}
	void change_menu_options()
	{
		mouse_pos = GetMousePosition();
		for (int i = 0; i < CANT_REC; i++) {
			if (CheckCollisionPointRec(mouse_pos, buttons[i])) {
				DrawRectangleRec(buttons[i], GRAY);
				if (CheckCollisionPointRec(mouse_pos, buttons[0]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
					gameState = GAME;
				if (CheckCollisionPointRec(mouse_pos, buttons[1]) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					substract_ball_speed();
				}
				if (CheckCollisionPointRec(mouse_pos, buttons[2]) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					add_ball_speed();
				}
				if (CheckCollisionPointRec(mouse_pos, buttons[4]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					switch (gameType)
					{
					case PvP:
					{
						gameType = PvB;
						break;
					}
					case PvB:
					{
						gameType = BvB;
						break;

					}
					case BvB:
					{
						gameType = PvP;
						break;
					}
					default:
						break;
					}
				}
				if (CheckCollisionPointRec(mouse_pos, buttons[6]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) set_random_color_player(players[PLAYER1]);
				if (CheckCollisionPointRec(mouse_pos, buttons[5]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) set_random_color_player(players[PLAYER2]);
			}
			else
				DrawRectangleRec(buttons[i], BROWN);


		}
	}

}
