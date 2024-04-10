#pragma once
#pragma once
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_

#include "BaseObject.h"
#include "CommonFunc.h"
#include "string.h"




class BulletObject :public BaseObject
{
public:
	BulletObject();
	~BulletObject();

	
	void action(SDL_Renderer* des,int k);
	

	void Set_Rect(const int& x_, const int& y_) { rect_.x = x_; rect_.y = y_; }

	void Loadac(SDL_Renderer* des);
	
	void set_tt (const int& tt_) { tt = tt_; }

	void set_cb_basic(int basic) { cb_basic = basic; }
	void set_unti(int unti_) { unti = unti_; }
	void set_basic_skill( int bs_skill) { basic_skill = bs_skill; }
	void set_system_basis();
private:
	
	int sel;
	float angle;
	int tt;
	int cb_basic;
	int unti;
	int basic_skill;
	std::vector<std::string > skill[3];
};


#endif // !1
