#include"Sound.h"

void Sound::LoadMusic(const char path[])
{
	sound = Mix_LoadWAV(path);

}

void Sound::DisplayMusic(int x)
{
	if (Mix_PlayingMusic() == 0) Mix_PlayChannel(-1,sound, x);

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
