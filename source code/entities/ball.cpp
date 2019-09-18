#include "ball.h"

Ball ball;
void init_ball()
{
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
	ball.img = LoadImage("resources/ball.png");
	ImageResize(&ball.img, ball.ball_radius + 30, ball.ball_radius + 30);
	ball.texture = LoadTextureFromImage(ball.img);
	UnloadImage(ball.img);
}
void substract_ball_speed()
{
	ball.ball_speed_init.x -= 0.2f;
	ball.ball_speed_init.y -= 0.2f;
	if (ball.ball_speed_init.x < 1) {
		ball.ball_speed_init.x = 1;
		ball.ball_speed_init.y = 1;
	}
	ball.ball_speed = ball.ball_speed_init;
}
void add_ball_speed()
{
	ball.ball_speed_init.x += 0.2f;
	ball.ball_speed_init.y += 0.2f;
	if (ball.ball_speed_init.x > 10) {
		ball.ball_speed_init.x = 10;
		ball.ball_speed_init.y = 10;
	}
	ball.ball_speed = ball.ball_speed_init;
}