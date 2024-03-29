#include "game_screen.h"


namespace Godziela
{
	bool game_start;
	float foo;

	void init_game_screen() {
		game_start = false;
	}

	void draw_game()
	{

		DrawTexture(background_texture, -30, 0, WHITE);
		if (!game_start)
			DrawText("Press Space", GetScreenWidth() / 2 - 70, GetScreenHeight() / 2 - 70, 20, RED);

		DrawText(FormatText("J1: %01i", players[PLAYER1].score), 10, 10, 20, players[PLAYER1].color);
		DrawText(FormatText("J2: %01i", players[PLAYER2].score), 700, 10, 20, players[PLAYER2].color);

		DrawRectangleRec(players[PLAYER1].rec, players[PLAYER1].color);
		DrawRectangleRec(players[PLAYER2].rec, players[PLAYER2].color);
		DrawTexture(players[PLAYER1].texture, static_cast<int>(players[PLAYER1].rec.x), static_cast<int>(players[PLAYER1].rec.y), players[PLAYER1].color);
		DrawTexture(players[PLAYER2].texture, static_cast<int>(players[PLAYER2].rec.x), static_cast<int>(players[PLAYER2].rec.y), players[PLAYER2].color);
		DrawCircleV(ball.ball_position, ball.ball_radius, ball.color);
		DrawTexture(ball.texture, static_cast<int>(ball.ball_position.x - 23), static_cast<int>(ball.ball_position.y - 23), WHITE);

		if (players[PLAYER1].score >= score_max || players[PLAYER2].score >= score_max) {
			gameState = END;
		}
	}

	void game_update()
	{
		PlayMusicStream(background_music);
		UpdateMusicStream(background_music);
		//Points
		if ((ball.ball_position.y >= (GetScreenHeight() - ball.ball_radius)) || (ball.ball_position.y <= ball.ball_radius)) ball.ball_speed.y *= -1.0f;
		if (ball.ball_position.x <= 0) {
			players[PLAYER2].score++;
			ball.ball_speed = ball.ball_speed_init;
			ball.ball_position = ball.ball_position_init;
			ball.color = WHITE;
			reset_pos_players();
			game_start = false;
		}
		if (ball.ball_position.x >= GetScreenWidth()) {
			players[PLAYER1].score++;
			reset_pos_players();
			ball.ball_position = ball.ball_position_init;
			ball.ball_speed = ball.ball_speed_init;
			ball.color = WHITE;
			game_start = false;
		}
		//Player-Ball Collision
		if (CheckCollisionCircleRec(ball.ball_position, ball.ball_radius, players[PLAYER1].rec) ||
			CheckCollisionCircleRec(ball.ball_position, ball.ball_radius, players[PLAYER2].rec)) {
			//In case that the sound problem gets resolved
			//PlaySound(hit_sound);
			ball.ball_speed.x *= -1.0f;
			foo = static_cast<float>(GetRandomValue(static_cast<int>(speedY.x), static_cast<int>(speedY.y)));
			ball.ball_speed.y = -1.0f * foo;
			if (ball.ball_speed.x < 0) {
				ball.ball_speed.x -= speed_up;
				ball.ball_speed.y -= speed_up;
				ball.ball_position.x -= ball.ball_radius;
				ball.color = players[PLAYER2].color;
			}
			else {
				ball.ball_speed.x += speed_up;
				ball.ball_speed.y += speed_up;
				ball.ball_position.x += ball.ball_radius;
				ball.color = players[PLAYER1].color;
			}
		}
		//wall player's collition
		if (players[PLAYER1].rec.y > GetScreenHeight() - 50) players[PLAYER1].rec.y = (float)GetScreenHeight() - 50;
		if (players[PLAYER1].rec.y < 0) players[PLAYER1].rec.y = 0;
		if (players[PLAYER2].rec.y > GetScreenHeight() - 50) players[PLAYER2].rec.y = (float)GetScreenHeight() - 50;
		if (players[PLAYER2].rec.y < 0) players[PLAYER2].rec.y = 0;
		if (game_start) {
			ball.ball_position.x += ball.ball_speed.x * GetFrameTime();
			ball.ball_position.y += ball.ball_speed.y * GetFrameTime();
		}
	}
}