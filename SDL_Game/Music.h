#pragma once
#ifndef MUSIC_H_
#define MUSIC_H_

#include"CommonFunc.h"

class Music
{
public:
	void LoadMusic(const char path[]);
	void DisplayMusic();
	void Volume(int volum);
	void stopMusic();
	void Free(); 
		void  resumeMusic();
private:

	Mix_Music* sound;
};




#endif // !MUSIC_H_
