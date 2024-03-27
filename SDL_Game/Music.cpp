#include"Music.h"

void Music::LoadMusic(const char path[])
{
	sound = Mix_LoadWAV(path);

}

void Music::DisplayMusic(int x)
{
	Mix_PlayChannel(-1, sound, x);

}

void Music::Volume(int volum)
{
	Mix_Volume(-1, volum);


}
void Music::Free()
{
	Mix_FreeChunk(sound);


}
void Music::stopMusic()
{
	Mix_HaltChannel(-1);
	
}
