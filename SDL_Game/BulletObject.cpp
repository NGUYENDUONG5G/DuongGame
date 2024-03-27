#include"stdafx.h"
#include "BulletObject.h"

BulletObject::BulletObject()
{
	x_pos_ = SCREEN_WIDTH/2;
	y_pos_ = 0;
	 x_val_=0;
	 y_val_=0;
	 map_x_=0;
	 map_y_=0;
	 width_frame_=0;
	 height_frame_=0;
	 frame_=0;
	 map_x_ = 0;
	 map_y_ = 0;
	 on_ground_ = false;
}

BulletObject::~BulletObject()
{



}


bool BulletObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret)
	{
		width_frame_ = rect_.w / 4;
		height_frame_ = rect_.h;



	}
	return  ret;
}



void BulletObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < 4; i++)
		{
			frame_clip_[i].x = width_frame_ * i;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}

}

void BulletObject::Show(SDL_Renderer* des)
{
	if(on_ground_==false)
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
	
}

void BulletObject::DoPlayer(Map& gMap)
{

	x_val_ = 0;
	y_val_ += 2;
	if (y_val_ >= 10)
	{
		y_val_ = 10;
	}

	if (x_pos_>mt_x)
	{
		x_val_ -= 8;
	}
	else if (x_pos_<mt_x)
	{
		x_val_ += 8;
	}



	CheckToMap(gMap);




}





void BulletObject::CheckToMap(Map& map_data)
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



			if ((map_data.tile[y1][x2] != BLANK_TILE) || (map_data.tile[y2][x2] != BLANK_TILE))
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



			if ((map_data.tile[y1][x1] != BLANK_TILE) || (map_data.tile[y2][x1] != BLANK_TILE))
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


			if ((map_data.tile[y2][x1] != BLANK_TILE) || (map_data.tile[y2][x2] != BLANK_TILE))
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



			if ((map_data.tile[y1][x1] != BLANK_TILE) || (map_data.tile[y1][x2] != BLANK_TILE))
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





SDL_Rect BulletObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = rect_.w;
	rect.h = rect_.h;
	return rect;



}


