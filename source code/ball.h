#ifndef BALL_H
#define BALL_H
#include "libraries.h"

struct Ball {
	Vector2 ball_position_init;
	Vector2 ball_position;
	Vector2 ball_speed_init;
	Vector2 ball_speed;
	int ball_radius;
	Color color;
	Texture2D texture;
	Image img;
};
extern Ball ball;
void init_ball();
void add_ball_speed();
void substract_ball_speed();



#endif