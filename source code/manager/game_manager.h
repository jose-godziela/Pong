#pragma once
#include "players.h"
#include "ball.h"
#include "menu_screen.h"
#include "game_screen.h"
#include "audio.h"
#include "game_over_screen.h"

const int screenWidth = 800;
const int screenHeight = 450; 
const int FPS = 60;
const int REC_WIDTH = 250;
const int REC_HEIGHT = 25;
const int buttons_X = 267; //800 divided by 3
extern Texture2D background_texture;
extern Image background_image;
extern Color base_background;

void play();