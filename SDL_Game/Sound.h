#pragma once
#ifndef SOUND_H_
#define SOUND_H_
#include "CommonFunc.h"
class Sound
{
public:
	void LoadMusic(const char path[]);
	void DisplayMusic(int x);
	void Volume(int volum);
	void stopMusic();
	void Free();
private:

	Mix_Chunk* sound;
};


#endif // !SOUND_H_
