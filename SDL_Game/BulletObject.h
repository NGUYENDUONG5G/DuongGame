#pragma once
#pragma once
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_

#include "BaseObject.h"
#include "CommonFunc.h"




class BulletObject :public BaseObject
{
public:
	BulletObject();
	~BulletObject();

	

	

	void set_x_pos(const int& xVal, const int& yVal) {
		x_pos_ = xVal;
		y_pos_ = yVal;
	}
	
	int get_x_bb() const { return x_pos_; }
	int get_y_bb() const { return y_pos_; }

	void set_XY(const int& x, const int& y)
	{

		x_pos_ = x;
		y_pos_ = y;
	}
	
	SDL_Rect GetRectFrame() ;
	
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

	void GPS(const int& x_) { mt_x = x_; }
	void SetMapXY(const int map_x, const int map_y)
	{
		map_x_ = map_x;
		map_y_ = map_y;
	}
private:
	float x_pos_;
	float y_pos_;
	float x_val_;
	float y_val_;
	int map_x_;
	int map_y_;
	int width_frame_;
	int height_frame_;
	int frame_;
	bool on_ground_;
	SDL_Rect frame_clip_[4];
	int mt_x;
	
};


#endif // !1
