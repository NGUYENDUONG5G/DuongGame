#include "stdafx.h"
#include "CommonFunc.h"


bool Impact::Impact_(const int& x, const int& y, SDL_Rect rect)
{
	if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) return true;
	return false;

}
