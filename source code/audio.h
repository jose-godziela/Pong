#pragma once
#include "libraries.h"
const float master_volume = 30.0f;

extern Music background_music;
extern Music gameOver_music;
extern Sound hit_sound;

void init_audio();
void close_audio();
