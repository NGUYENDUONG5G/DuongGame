#pragma once
#pragma once
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"


#define THREAT_FRAME_NUM 4
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_SPEED 3



class ThreatsObject :public BaseObject
{
public:
	ThreatsObject();
	~ThreatsObject();

	enum TypeMove
	{
		STATIC_THREAT = 0,
		MOVE_IN_SPACE_THREAT = 1,
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


	void InitThreats();

	void set_type_move(const int& typeMove) { type_move_ = typeMove; }

	

	void set_input_left(const int& ipleft) { input_type_.left_ = ipleft; }
	void ImpMoveType(SDL_Renderer* screen);


	// bot tấn công

	std::vector <BulletObject*> get_bullet_list() const { return bullet_list_; }
	void set_bullet_list(const std::vector<BulletObject*>& bl_list) { bullet_list_ = bl_list; }

	void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);

	void RemoveBullet(const int& idx);
	void ktraN(const float& x, const float& y)
	{
		vt_x = x;
		vt_y = y;
	}

private:

	
	float vt_x;
	float vt_y;
	int map_x_;
	int map_y_;
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	bool on_ground_;
	int come_back_time_;
	SDL_Rect frame_clip_[THREAT_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;

	int type_move_;


	Input input_type_;

	std::vector<BulletObject*>bullet_list_;
};




#endif // !THREATS_OBJECT_H_
