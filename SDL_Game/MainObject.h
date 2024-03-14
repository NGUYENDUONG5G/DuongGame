#pragma once
#pragma once
#ifndef  MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <string>


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

	


	};
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();
	void Doplayer(Map& map_data);
	void CheckToMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y)
	{
		map_x_ = map_x;
		map_y_ = map_y;
	}
	void CenterEntityOnMap(Map& map_data);
	void UpdateImagePlayer(SDL_Renderer* des);



	void set_bullet_list(std::vector<BulletObject*> bullet_list)
	{
		p_bullet_list_ = bullet_list;
	}

	std::vector<BulletObject*> get_bullet_list() const { return p_bullet_list_; }

	void HandleBullet(SDL_Renderer* des);
	void RemoveBullet(const int& idx);


	
	int  vitri_x() { return x_pos_; }
	int vitri_y() { return y_pos_; }
	
	void Swap(const float& x, const float& y)
	{
		swx = x;
		swy = y;
	}
	
private:
	

	std::vector<BulletObject*> p_bullet_list_;
	
	float swx;
	float swy;
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	int width_frame_;
	int height_frame_;
	

	SDL_Rect frame_clip_[4];

	Input input_type_;
	int frame_;
	int dem;

	int status_;

	bool on_ground_;

	int map_x_;
	int map_y_;

	int come_back_time_;
	int check;
	
};


#endif