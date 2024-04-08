#include "stdafx.h"

#include "ThreatsObject.h"
#include <cmath>
#include <random>
#include <iostream>

ThreatsObject::ThreatsObject()
{
	width_frame_ = 0;
	height_frame_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	x_pos_ = SCREEN_WIDTH;
	y_pos_ = 0;
	on_ground_ = 0;
	
	frame_ = 0;
	status_=WALK_NONE,

	input_type_.left_ = 0;
	
	dem = 0;
	fight = 0;
	time_skill = 0;
	rad = 0;
}




ThreatsObject::~ThreatsObject()
{


}
bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret)
	{
		width_frame_ = rect_.w / 4;
		height_frame_ = rect_.h;



	}
	return  ret;
}



void ThreatsObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < 4; i++)
		{
			frame_clip_[i].x = width_frame_*i;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}

}

void ThreatsObject::Show(SDL_Renderer* des)
{

		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;
		if (frame_ >= 4)
		{
			frame_ = 0;
		}

		SDL_Rect* currentClip = &frame_clip_[frame_];
		SDL_Rect rendQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };
		SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);

	
}

void ThreatsObject::RandomAction()
{
	std::srand(std::time(NULL));
	
	if (time_skill == 0)
	{
		
		if (x_pos_ > vt_x)
		{
			rad = rand() % 2 + 2;
		
			
			
		}
		else if (x_pos_ < vt_x)
		{
			rad = rand() % 2;
				

		}
		time_skill++;
	}
	else
	{
		time_skill++;
		std::cout << rad << '\n';
		if (rad == 0)
		{
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			input_type_.up_right_ = 0;
			input_type_.up_left_ = 0;

		}
		else if (rad == 1)
		{

			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.up_right_ = 1;
			input_type_.up_left_ = 0;
		}
		else if(rad==2)
		{

			input_type_.right_ = 0;
			input_type_.left_ = 1;
			input_type_.up_right_ = 0;
			input_type_.up_left_ = 0;
		}
		else if (rad == 3)
		{
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.up_right_ = 0;
			input_type_.up_left_ = 1;
		}

		if (time_skill >= AI[rad]) time_skill = 0;
	}
}



void ThreatsObject::DoPlayer(Map& gMap)
{
	
		x_val_ = 0;
		y_val_ += THREAT_GRAVITY_SPEED;
		if (y_val_ >= THREAT_MAX_FALL_SPEED)
		{
			y_val_ = THREAT_MAX_FALL_SPEED;
		}
		else if (y_val_ <= THREAT_FLY)
		{
			y_val_ = THREAT_FLY;
		}
		if (y_pos_ <= 0) y_pos_ = 0;
		if (input_type_.left_ == 1)
		{
			x_val_ -= THREAT_SPEED;
		}
		else if (input_type_.right_ == 1)
		{
			x_val_ += THREAT_SPEED;
		}
		
		else if (input_type_.up_right_ == 1)
		{
			if (on_ground_ == true)
			{
				x_val_ += THREAT_SPEED;
				y_val_ -= 20;
				on_ground_ = false;
			}
		}
		else if (input_type_.up_left_ == 1)
		{
			if (on_ground_ == true)
			{
				x_val_ -= THREAT_SPEED;
				y_val_ -= 20;
				on_ground_ = false;
			}
		}
		
		CheckToMap(gMap);

	


}





void ThreatsObject::CheckToMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0)
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];



			if ((map_data.tile[y1][x2] != BLANK_TILE ) || (map_data.tile[y2][x2] != BLANK_TILE ))
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;

			}


		}

		else if (x_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];



			if ((map_data.tile[y1][x1] != BLANK_TILE ) || (map_data.tile[y2][x1] != BLANK_TILE ))
			{
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;



			}



		}





	}


	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{

			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];


			if ((map_data.tile[y2][x1] != BLANK_TILE ) || (map_data.tile[y2][x2] != BLANK_TILE ))
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= height_frame_ + 1;

				y_val_ = 0;
				on_ground_ = true;



			}



		}

		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];



			if ((map_data.tile[y1][x1] != BLANK_TILE ) || (map_data.tile[y1][x2] != BLANK_TILE ))
			{
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;


			}



		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) x_pos_ = 0;
	else if (x_pos_ + width_frame_ > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}

	

}

//t
void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
	
			//đảo chiều

		if (x_pos_ > vt_x)
		{
				
				if (x_pos_ - vt_x > 64*2 )
				{
					LoadImg("img//bot_none_left.png", screen);
				}
				else
				{
					input_type_.left_ = 0;
					LoadImg("img//bot_fight_left.png", screen);
				}
			


		}
		else if (x_pos_ < vt_x)
		{
			
				
			
				if (vt_x - x_pos_ > 64*2)
				{
					LoadImg("img//bot_none_right.png", screen);
				}
				else
				{
					
					LoadImg("img//bot_fight_right.png", screen);

				}
		}
	

}








SDL_Rect ThreatsObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;
	return rect;
}
int ThreatsObject:: sent_fight()
{
	if (dem % 3 == 0) fight = 1;
	else fight = 0;
	dem++;
	return fight;

}