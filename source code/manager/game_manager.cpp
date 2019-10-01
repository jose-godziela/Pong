#include "game_manager.h"


namespace Godziela
{
	Texture2D background_texture;
	Image background_image;
	Color base_background;


	static void close_all();
	static void draw();
	static void game();
	static void init();
	static void input();
	static void mov_ia();
	static void update();
	static void init_buttons();

	void play() {

		init();
		game();
	}

	static void init() {
		game_start = false;
		InitWindow(screenWidth, screenHeight, "YEET: ATARI 2600 VERSION");

		init_audio();
		init_game_over();
		init_game_screen();

		//Sound doesn't load "Invalid data header"
		//Tried both LoadSoundFromWave & LoadSound
		//hit_sound = LoadSound("resources/sound/hit.wav");

		//BackGround Creation
		background_image = LoadImage("resources/images/fondo.png");
		ImageResize(&background_image, screenWidth + 60, screenHeight);
		background_texture = LoadTextureFromImage(background_image);
		UnloadImage(background_image);

		frames = 0;

		init_players();
		init_ball();

		base_background = BLACK;

		init_buttons();

		gameState = MENU;
	}

	static void game() {
		while (!WindowShouldClose())
		{
			input();
			update();
			draw();
		}
		close_all();
	}

	static void update()
	{
		switch (gameState)
		{
		case MENU:
		{
			change_menu_options();
			break;
		}
		case GAME:
		{
			game_update();
			break;
		}
		case END:
		{
			draw_game_over();
			break;
		}
		}
	}

	static void input() {
		if (game_start && gameType != BvB) {
			//Enables Player 1 controls
			//Enters here even in PvB
			if (IsKeyDown(KEY_W)) players[PLAYER1].rec.y -= vel_player * GetFrameTime();
			if (IsKeyDown(KEY_S)) players[PLAYER1].rec.y += vel_player * GetFrameTime();
			//Enables Player 2 Controls
			//Checks if the gameType is versus a player or a bot
			if (gameType == PvP) {
				if (IsKeyDown(KEY_UP)) players[PLAYER2].rec.y -= vel_player * GetFrameTime();
				if (IsKeyDown(KEY_DOWN)) players[PLAYER2].rec.y += vel_player * GetFrameTime();
			}
			//If the game is PvB
			else {
				mov_ia();
			}
		}
		//If the game is BvB
		else {
			mov_ia();
		}

		if (IsKeyDown(KEY_SPACE) && gameState == GAME) {
			game_start = true;
		}
	}
	static void draw() {
		BeginDrawing();
		ClearBackground(base_background);
		switch (gameState) {
		case MENU:
			draw_menu();
			break;
		case GAME: {
			draw_game();
			break;
		}
		case END: {
			draw_game_over();
		}
		}
		EndDrawing();
	}

	static void mov_ia() {
		if (gameType != PvP) {
			if (ball.ball_position.y < players[PLAYER2].rec.y && ball.ball_position.x >= GetScreenWidth() / 2) {
				players[PLAYER2].rec.y -= vel_player * GetFrameTime();
			}
			if (ball.ball_position.y > players[PLAYER2].rec.y && ball.ball_position.x >= GetScreenWidth() / 2) {
				players[PLAYER2].rec.y += vel_player * GetFrameTime();
			}
			if (gameType == BvB) {
				if (ball.ball_position.y < players[PLAYER1].rec.y && ball.ball_position.x <= GetScreenWidth() / 2) {
					players[PLAYER1].rec.y -= vel_player * GetFrameTime();
				}
				if (ball.ball_position.y > players[PLAYER1].rec.y && ball.ball_position.x <= GetScreenWidth() / 2) {
					players[PLAYER1].rec.y += vel_player * GetFrameTime();
				}
			}
		}
	}

	static void close_texture()
	{
		UnloadTexture(background_texture);
		UnloadTexture(players[PLAYER1].texture);
		UnloadTexture(players[PLAYER2].texture);
	}

	static void close_all() {
		//If hit_sound error is solved
		//UnloadSound(hit_sound);
		close_audio();
		close_texture();
		CloseWindow();
	}

	static void init_buttons()
	{
		int buttons_Y = screenHeight - 140;

		for (int i = 0; i < CANT_REC; i++)
		{
			buttons[i].height = REC_HEIGHT;
			buttons[i].width = REC_WIDTH;
			buttons[i].x = (float)buttons_X;
			buttons[i].y = (float)buttons_Y;
			buttons_Y -= 45;

			//Change color creation
			if (i > 4)
			{
				buttons[i].height = 20;
				buttons[i].width = 50;
				buttons[i].x = (float)(GetScreenWidth() / 14);
				buttons[i].y = (float)(GetScreenHeight() / (i - 2));
			}

		}
	}
}