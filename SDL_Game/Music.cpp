#include"Music.h"

void Music::LoadMusic(const char path[])
{
	sound = Mix_LoadMUS(path);

}

void Music::DisplayMusic()
{
	if (Mix_PlayingMusic() == 0) Mix_PlayMusic(sound, -1);

}

void Music::Volume(int volum)
{
	Mix_Volume(-1, volum);


}
void Music::Free()
{
	Mix_FreeMusic(sound);


}
void Music::stopMusic()
{
	Mix_HaltMusic();
	
}
