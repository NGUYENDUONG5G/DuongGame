#pragma once
#ifndef ROOM_IMG_H_
#define ROOM_IMG_H

#include "CommonFunc.h"
#include"BaseObject.h"

class RoomImg :public BaseObject
{
public:
	RoomImg();
	~RoomImg();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void practice(SDL_Renderer* screen);
	float sent_room() { return room; }
	void set_room(float room_) { room = room_; }
private:
	float room;
	

};

#endif // !ROOM_IMG_H_
