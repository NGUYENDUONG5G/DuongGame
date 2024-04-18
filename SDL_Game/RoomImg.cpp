#include"RoomImg.h"
#include"CommonFunc.h"
#include "BaseObject.h"

RoomImg::RoomImg()
{
	room = 0;
 }
RoomImg::~RoomImg()
{
	;
}
bool RoomImg::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg( path, screen);
	return ret;
}

void RoomImg::practice(SDL_Renderer* screen)
{
	
	if (room <=1 ) room+=0.1;

	float w = room * rect_.w;
	float h = room * rect_.h;
	SDL_Rect roomy = { SCREEN_WIDTH / 2 - w / 2,SCREEN_HEIGHT / 2 - h / 2,w,h };
	SDL_RenderCopy(screen, p_object_, NULL, &roomy);
}