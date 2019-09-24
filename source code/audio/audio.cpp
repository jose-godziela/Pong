#include "audio.h"

namespace Godziela
{
	Music background_music;
	Music gameOver_music;


	void init_audio()
	{
		InitAudioDevice();
		SetMasterVolume(master_volume);
		gameOver_music = LoadMusicStream("resources/music/gameOver.ogg");
		background_music = LoadMusicStream("resources/music/GoodOldTimes.ogg");
	}

	void close_audio()
	{
		UnloadMusicStream(background_music);
		UnloadMusicStream(gameOver_music);
		CloseAudioDevice();
	}
}