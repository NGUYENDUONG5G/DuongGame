#include"Sound.h"

void Sound::LoadMusic(const char path[])
{
	
	sound = Mix_LoadWAV(path);

}

void Sound::DisplayMusic()
{
	
	Mix_PlayChannel(-1, sound,0 );
}

void Sound::Volume(int volum)
{
	Mix_Volume(-1, volum);


}
void Sound::Free()
{
	Mix_FreeChunk(sound);


}
void Sound::stopMusic()
{
	Mix_HaltChannel(-1);

}

