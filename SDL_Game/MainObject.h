#pragma once
#pragma once
#ifndef  MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <string>
#include "Music.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 10		
#define PLAYER_JUMP_VAL 18


class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();
	enum WalkType
	{
		WALK_NONE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_UP=3,
		WALK_DOWN=4,
		WAR1=5,
		WAR2=6,
		WAR3=7,
		WAR4=8,

	


	};
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();
	void Doplayer(Map& map_data,SDL_Renderer* screen);
	void CheckToMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y)
	{
		map_x_ = map_x;
		map_y_ = map_y;
	}
	void CenterEntityOnMap(Map& map_data);
	void UpdateImagePlayer(SDL_Renderer* des);



	
	void set_vt(const int& x, const int& y) {

		x_pos_ = x;
		y_pos_ = y;
	}
	
	void set_xpos(const int& xpos) { x_pos_ = xpos; }
	SDL_Rect GetRectFrame();
void set_xval_(const int& xval)   {  x_val_= xval; }
	int  vitri_x() { return x_pos_; }
	int vitri_y() { return y_pos_; }
	
	void Swap(const float& x, const float& y)
	{
		swx = x;
		swy = y;
	}
	

	
	int set_check() const { return check; }
	int get_heiy() { return heiy; }

	int  set_fight() { return fight; }
	float sent_max_y() { return max_y; }
	float sent_min_y() { return min_y; }
	
	int cb_basic_() { return cb_basic; }
	int is_basic_() { return is_basic; }
	int sent_unti() const { return unti; }
private:
	

	
	int heiy;
	float swx;
	float swy;
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	int width_frame_;
	int height_frame_;
	float max_y;
	float min_y;
	float angle;
	SDL_Rect frame_clip_[4];

	Input input_type_;
	int frame_;
	int dem;

	int status_;

	bool on_ground_;

	int map_x_;
	int map_y_;

	
	int check;
	int fight;
	
	
	int cb_basic;
	int is_basic;
	int unti;
	int time_unti;
	
};


#endif