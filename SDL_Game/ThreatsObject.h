﻿#pragma once
#pragma once
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"


#define THREAT_FRAME_NUM 8
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_SPEED 3
#define THREAT_JUMP 18


class ThreatsObject :public BaseObject
{
public:
	ThreatsObject();
	~ThreatsObject();

	enum WalkType
	{
		WALK_NONE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_UP = 3,
		WALK_DOWN = 4,
		WAR1 = 5,
		WAR2 = 6,
	
	};

	void set_x_val(const float& xVal) {
		x_val_ = xVal;
	}

	void set_y_val(const float& yVal) {
		y_pos_ = yVal;
	}

	void set_x_pos(const float& xp) {
		x_pos_ = xp;
	}
	void set_y_pos(const float& yp) {
		y_pos_ = yp;
	}

	void set_vt(const float& x, const float& y) {
		x_pos_ = x;
		y_pos_ = y;
	}
	float get_x_pos() const {
		return x_pos_;
	}
	float get_y_pos() const {
		return y_pos_;
	}

	void SetMapXY(const int& mp_x, const int& mp_y) {
		map_x_ = mp_x; map_y_ = mp_y;
	}
	void set_clips();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	int get_width_frame() const {
		return width_frame_;
	}
	int get_height_frame() const {
		return height_frame_;
	}
	// Hành động cho bot
	
	void DoPlayer(Map& gMap);
	
	void CheckToMap(Map& gMap);


	

	void set_type_move(const int& typeMove) { type_move_ = typeMove; }

	

	void set_input_left(const int& ipleft) { input_type_.left_ = ipleft; }
	void ImpMoveType(SDL_Renderer* screen);


	// bot tấn công

	

	
	int sent_fight();
	
	


	void ktraN(const float& x, const float& y,const int& z)
	{
		vt_x = x;
		vt_y = y;
		tt = z;
	}
	


	SDL_Rect GetRectFrame();

	
	
private:

	int tt;
	float vt_x;
	float vt_y;
	int map_x_;
	int map_y_;
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	bool on_ground_;
	int status_;
	
	SDL_Rect frame_clip_[THREAT_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;

	int type_move_;

	int dem;
	int fight;
	Input input_type_;

	
};




#endif // !THREATS_OBJECT_H_
