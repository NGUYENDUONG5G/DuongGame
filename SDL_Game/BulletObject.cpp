#include"stdafx.h"
#include "BulletObject.h"
#include <math.h>

BulletObject::BulletObject()
{

	sel = 0;
	angle = 0.0;
	tt = 0;
	cb_basic = 0;
	unti = 0;
}

BulletObject  ::~BulletObject()
{
	;
}
void BulletObject::Loadac(SDL_Renderer* screen)
{
	if (unti == 0)
	{
		if (tt == 0)
		{

			LoadImg("img//knife_left.png", screen);
		}
		else
		{
			LoadImg("img//knife_right.png", screen);

		}
	}
	else if (unti == 1)
	{

		LoadImg("img//knife_around.png", screen);
	}
}
	
	




void BulletObject::action(SDL_Renderer* screen,int k)
{
	if (cb_basic == 1)
	{
		if (tt == 1) angle += 20;
		else angle -= 20;
	}
	else if (unti == 1)
	{
		angle += 20;
	}
	else angle = 0;
	if (abs(angle) > k) angle = 0;


	BaseObject::Render(screen, angle, NULL);

}