#include "raylib.h"
#include "glfw3.h"

const int TOTAL_PLAYERS = 2;
const int PLAYER1 = 0;
const int PLAYER2 = 1;
const int FPS = 60;
const int MOVEMENT = 22;
const int TEN_SEC = 600;
const int MAX_COLOR = 6;
const int CANT_REC = 7;
const int REC_WIDTH = 250;
const int REC_HEIGHT = 25;
const int screenWidth = 800;
const int screenHeight = 450;
const int score_max = 5;
const int buttons_X = 800 / 3;
const float master_volume = 30.0f;
const float speed_up = 0.5f;
const float posX_player1 = screenWidth / 15;
const float posX_player2 = (float)screenWidth - ((float)screenWidth / 12);
const float posY_players = (float)screenHeight / 2;
const float vel_player = 5.0f;
const Vector2 speedY = { 5, 10 };
Vector2 mouse_pos = { 0,0 };
Rectangle buttons[CANT_REC];
Image img;
Music background_music;
Music gameOver_music;
Wave wav;
Sound hit_sound;

struct Player {
	Rectangle rec;
	Vector2 size;
	int score;
	Color color;
	Texture2D texture;
};

Player players[TOTAL_PLAYERS];

struct Ball {
	Vector2 ball_position_init;
	Vector2 ball_position;
	Vector2 ball_speed_init;
	Vector2 ball_speed;
	int ball_radius;
	Color color;
	Texture2D texture;
};
Ball ball;

enum GameState {
	MENU,
	GAME,
	END
};

GameState gameState;

enum GameType {
	PvP,	//Player vs Player
	PvB,	//Player vs Bot
	BvB		//Bot vs Bot
};

GameType gameType;

void init();
void game();
void play();
void update();
void draw();
void input();
void movIA();
void close_all();
void setRandomColorPlayer(Player &p);
int frames;
bool game_start;
Color base_background;
Image background_image;
Texture2D background_texture;

int main()
{
	play();
	return 0;
}

void play() {
	init();
	game();
}
void init() {
	game_start = false;
	InitWindow(screenWidth, screenHeight, "YEET: ATARI 2600 VERSION");

	InitAudioDevice();
	SetMasterVolume(master_volume);
	background_music = LoadMusicStream("resources/music/GoodOldTimes.ogg");
	gameOver_music = LoadMusicStream("resources/music/gameOver.ogg");

	//Sound doesn't load "Invalid data header"
	//Tried both LoadSoundFromWave & LoadSound
	hit_sound = LoadSound("resources/sound/hit.wav");

	//BackGround Creation
	background_image = LoadImage("resources/fondo.png");
	ImageResize(&background_image, screenWidth + 60, screenHeight);
	background_texture = LoadTextureFromImage(background_image);
	UnloadImage(background_image);

	frames = 0;
	//Ball Creation
	ball.ball_position_init.x = GetScreenWidth() / 2;
	ball.ball_position_init.y = GetScreenHeight() / 2;
	ball.ball_position = ball.ball_position_init;
	ball.ball_speed_init.x = 5.0f;
	ball.ball_speed_init.y = 4.0f;
	ball.ball_speed = ball.ball_speed_init;
	ball.ball_radius = 20;
	ball.color = WHITE;
	//Ball texure
	img = LoadImage("resources/ball.png");
	ImageResize(&img, ball.ball_radius + 30, ball.ball_radius + 30);
	ball.texture = LoadTextureFromImage(img);
	UnloadImage(img);

	//Player Creation
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
		img = LoadImage("resources/players.png");
		ImageRotateCW(&img);
		ImageResize(&img, (int)players[i].size.x, (int)players[i].size.y);
		players[i].texture = LoadTextureFromImage(img);
		UnloadImage(img);

	}
	//Player 2 Position and base color
	players[PLAYER2].rec.x = posX_player2;
	players[PLAYER2].color = RED;

	base_background = BLACK;

	int buttons_Y = screenHeight - 140;

	for (int i = 0; i < CANT_REC; i++)
	{
		buttons[i].height = REC_HEIGHT;
		buttons[i].width = REC_WIDTH;
		buttons[i].x = buttons_X;
		buttons[i].y = buttons_Y;
		buttons_Y -= 45;

		//Change color creation
		if (i > 4)
		{
			buttons[i].height = 20;
			buttons[i].width = 50;
			buttons[i].x = GetScreenWidth() / 14;
			buttons[i].y = GetScreenHeight() / (i - 2);
		}

	}

	gameState = MENU;
	SetTargetFPS(FPS);
}

void game() {
	while (!WindowShouldClose())
	{
		input();
		update();
		draw();
	}
	close_all();
}

void update() {
	switch (gameState)
	{
	case MENU: {
		for (int i = 0; i < CANT_REC; i++) {
			if (CheckCollisionPointRec(mouse_pos, buttons[i])) {
				DrawRectangleRec(buttons[i], GRAY);
				if (CheckCollisionPointRec(mouse_pos, buttons[0]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
					gameState = GAME;
				if (CheckCollisionPointRec(mouse_pos, buttons[1]) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					ball.ball_speed_init.x -= 0.2f;
					ball.ball_speed_init.y -= 0.2f;
					if (ball.ball_speed_init.x < 1) {
						ball.ball_speed_init.x = 1;
						ball.ball_speed_init.y = 1;
					}
				}
				if (CheckCollisionPointRec(mouse_pos, buttons[2]) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					ball.ball_speed_init.x += 0.2f;
					ball.ball_speed_init.y += 0.2f;
					if (ball.ball_speed_init.x > 10) {
						ball.ball_speed_init.x = 10;
						ball.ball_speed_init.y = 10;
					}
					ball.ball_speed = ball.ball_speed_init;
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
				if (CheckCollisionPointRec(mouse_pos, buttons[6]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) setRandomColorPlayer(players[PLAYER1]);
				if (CheckCollisionPointRec(mouse_pos, buttons[5]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) setRandomColorPlayer(players[PLAYER2]);
			}
			else
				DrawRectangleRec(buttons[i], BROWN);


		}
		mouse_pos = GetMousePosition();
		break;
	}
	case GAME: {
		PlayMusicStream(background_music);
		UpdateMusicStream(background_music);
		//Ball Collition
		if ((ball.ball_position.y >= (GetScreenHeight() - ball.ball_radius)) || (ball.ball_position.y <= ball.ball_radius)) ball.ball_speed.y *= -1.0f;
		if (ball.ball_position.x <= 0) {
			players[PLAYER2].score++;
			ball.ball_speed = ball.ball_speed_init;
			ball.ball_position = ball.ball_position_init;
			ball.color = WHITE;
			players[PLAYER1].rec.x = posX_player1;
			players[PLAYER1].rec.y = posY_players;
			players[PLAYER2].rec.x = posX_player2;
			players[PLAYER2].rec.y = posY_players;
			game_start = false;
		}
		if (ball.ball_position.x >= GetScreenWidth()) {
			players[PLAYER1].score++;
			players[PLAYER1].rec.x = posX_player1;
			players[PLAYER1].rec.y = posY_players;
			players[PLAYER2].rec.x = posX_player2;
			players[PLAYER2].rec.y = posY_players;
			ball.ball_position = ball.ball_position_init;
			ball.ball_speed = ball.ball_speed_init;
			ball.color = WHITE;
			game_start = false;
		}
		//Player Collision
		if (CheckCollisionCircleRec(ball.ball_position, ball.ball_radius, players[PLAYER1].rec) ||
			CheckCollisionCircleRec(ball.ball_position, ball.ball_radius, players[PLAYER2].rec)) {
			//In case that the sound problem gets resolved
			//PlaySound(hit_sound);
			ball.ball_speed.x *= -1.0f;
			ball.ball_speed.y = -(GetRandomValue(speedY.x, speedY.y));
			ball.ball_speed.y *= -1.0f;
			if (ball.ball_speed.x < 0) {
				ball.ball_speed.x -= speed_up;
				ball.ball_speed.y -= speed_up;
				ball.ball_position.x -= MOVEMENT;
				ball.color = players[PLAYER2].color;
			}
			else {
				ball.ball_speed.x += speed_up;
				ball.ball_speed.y += speed_up;
				ball.ball_position.x += MOVEMENT;
				ball.color = players[PLAYER1].color;
			}
		}
		//wall player's collition
		if (players[PLAYER1].rec.y > screenHeight - 50) players[PLAYER1].rec.y = screenHeight - 50;
		if (players[PLAYER1].rec.y < 0) players[PLAYER1].rec.y = 0;
		if (players[PLAYER2].rec.y > screenHeight - 50) players[PLAYER2].rec.y = screenHeight - 50;
		if (players[PLAYER2].rec.y < 0) players[PLAYER2].rec.y = 0;
		if (game_start) {
			ball.ball_position.x += ball.ball_speed.x;
			ball.ball_position.y += ball.ball_speed.y;
		}
		break;
	}
	}


}

void input() {
	if (game_start && gameType != BvB) {
		//Player 1 controls
		//Enters here even in PvB
		if (IsKeyDown(KEY_UP)) players[PLAYER2].rec.y -= vel_player;
		if (IsKeyDown(KEY_DOWN)) players[PLAYER2].rec.y += vel_player;
		//Player 2 Controls
		//Checks if the gameType is versus a player or a bot
		if (gameType == PvP) {
			if (IsKeyDown(KEY_W)) players[PLAYER1].rec.y -= vel_player;
			if (IsKeyDown(KEY_S)) players[PLAYER1].rec.y += vel_player;
		}
		//If the game is PvB
		else {
			movIA();
		}
	}
	//If the game is BvB
	else {
		movIA();
	}

	if (IsKeyDown(KEY_SPACE)) {
		game_start = true;
	}
}
void draw() {
	BeginDrawing();
	ClearBackground(base_background);
	switch (gameState) {
	case MENU:
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

		break;
	case GAME: {

		DrawTexture(background_texture, -30, 0, WHITE);
		if (!game_start)
			DrawText("Press Space", GetScreenWidth() / 2 - 70, GetScreenHeight() / 2 - 70, 20, RED);

		DrawText(FormatText("J1: %01i", players[PLAYER1].score), 10, 10, 20, players[PLAYER1].color);
		DrawText(FormatText("J2: %01i", players[PLAYER2].score), 700, 10, 20, players[PLAYER2].color);

		DrawRectangleRec(players[PLAYER1].rec, players[PLAYER1].color);
		DrawRectangleRec(players[PLAYER2].rec, players[PLAYER2].color);
		DrawTexture(players[PLAYER1].texture, players[PLAYER1].rec.x, players[PLAYER1].rec.y, players[PLAYER1].color);
		DrawTexture(players[PLAYER2].texture, players[PLAYER2].rec.x, players[PLAYER2].rec.y, players[PLAYER2].color);
		DrawCircleV(ball.ball_position, ball.ball_radius, ball.color);
		DrawTexture(ball.texture, ball.ball_position.x - 23, ball.ball_position.y - 23, WHITE);

		if (players[PLAYER1].score >= score_max || players[PLAYER2].score >= score_max) {
			gameState = END;
		}

		break;
	}
	case END: {
		StopMusicStream(background_music);
		PlayMusicStream(gameOver_music);
		UpdateMusicStream(gameOver_music);
		DrawText("GAME OVER", GetScreenWidth() / 3, GetScreenHeight() / 2.5f, 50, RED);
		frames++;

		if (frames > TEN_SEC)
		{
			players[PLAYER1].score = 0;
			players[PLAYER2].score = 0;
			game_start = false;
			gameState = MENU;
			StopMusicStream(gameOver_music);
		}
	}
	}
	EndDrawing();
}

void setRandomColorPlayer(Player &p) {
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

void movIA() {
	if (gameType != PvP) {
		if (ball.ball_position.y < players[PLAYER2].rec.y) {
			players[PLAYER2].rec.y -= vel_player;
		}
		if (ball.ball_position.y > players[PLAYER2].rec.y) {
			players[PLAYER2].rec.y += vel_player;
		}
		if (gameType == BvB) {
			if (ball.ball_position.y < players[PLAYER1].rec.y) {
				players[PLAYER1].rec.y -= vel_player;
			}
			if (ball.ball_position.y > players[PLAYER1].rec.y) {
				players[PLAYER1].rec.y += vel_player;
			}
		}
	}
}

void close_all() {
	//If hit_sound error is solved
	//UnloadSound(hit_sound);
	UnloadMusicStream(background_music);
	UnloadMusicStream(gameOver_music);
	UnloadTexture(background_texture);
	UnloadTexture(players[PLAYER1].texture);
	UnloadTexture(players[PLAYER2].texture);
	CloseAudioDevice();
	CloseWindow();
}