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
	basic_skill = 0;
}

BulletObject  ::~BulletObject()
{
	;
}


void BulletObject::set_system_basis()
{
	skill[5] = { "img//double_knife_left.png","img//double_knife_right.png" };
	skill[4] = { "img//spear_left.png","img//spear_right.png" };
	skill[3] = { "img//knife2_left.png","img//knife2_right.png" };
	skill[2] = { "img//knife_left.png","img//knife_right.png" };
	skill[1] = { "img//axe_left.png","img//axe_right.png" };
	skill[0] = { "img//hand_left.png","img//hand_right.png" };


}
void BulletObject::Loadac(SDL_Renderer* screen)
{
	if (unti == 0)
	{
		if (tt == 0)
		{

			LoadImg(skill[basic_skill][0], screen);
		}
		else
		{
			LoadImg(skill[basic_skill][1], screen);

		}
	}
	else if (unti == 1)
	{

		LoadImg("img//unti.png", screen);
	}
}
	
	




void BulletObject::action(SDL_Renderer* screen,int k)
{
	if (cb_basic == 1)
	{
		if (tt == 1) angle += 30;
		else angle -= 30;
	}
	else if (unti == 1)
	{
		angle += 10;
	}
	else angle = 0;
	if (abs(angle) > k) angle = 0;


	BaseObject::Render(screen, angle, NULL);

}