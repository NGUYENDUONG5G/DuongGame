#pragma once
#ifndef MUSIC_H_
#define MUSIC_H_

#include"CommonFunc.h"

class Music
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




#endif // !MUSIC_H_
