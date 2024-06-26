﻿#include "stdafx.h"
#include "MainObject.h"
#include"BaseObject.h"
#include"BulletObject.h"
#include <iostream>
#include<cmath>





MainObject::MainObject() {
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = WALK_NONE;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	on_ground_ = false;
	map_x_ = 0;
	map_y_ = 0;
	angle = 0;
	fight = 0;

	check = 1;
	is_basic = 0;
	none_basic = 0;
	cb_basic = 0;
	unti = 2;
	time_unti = 0;
	time_move_skill = 0;
}
MainObject::~MainObject() {



}
//refer from : https://phattrienphanmem123az.com/
bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true) {
		width_frame_ = rect_.w / 4;
		height_frame_ = rect_.h;

	}
	return ret;

}


SDL_Rect MainObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;
	return rect;
}
//refer from : https://phattrienphanmem123az.com/
void MainObject::set_clips()
{
	
	if (width_frame_ > 0 && height_frame_ > 0) {
		
		for (int i = 0; i < 4; i++)
		{
			frame_clip_[i].x = width_frame_*i;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
		
	}

}
//refer from : https://phattrienphanmem123az.com/
void MainObject::Show(SDL_Renderer* des) {
	UpdateImagePlayer(des);

	frame_++;

	if (frame_ >= 4) frame_ = 0;

	
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		SDL_Rect* current_clip = &frame_clip_[frame_];
		SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };
		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	





}
void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen,int pk) {
	if (pk == 1)
	{
		if (events.type == SDL_KEYDOWN)
		{

			switch (events.key.keysym.sym)
			{

			case SDLK_v:
			{
				status_ = WALK_RIGHT;
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				cb_basic = 0;
				none_basic = 1;
				is_basic = 1;
				check = 1;
				
				UpdateImagePlayer(screen);
			}
			break;
			case SDLK_c:
			{
				status_ = WALK_LEFT;

				input_type_.left_ = 1;
				input_type_.right_ = 0;
				cb_basic = 0;
				check = 0;
				none_basic = 1;
				is_basic = 1;
				UpdateImagePlayer(screen);
			}
			break;

			case SDLK_f:
			{
				input_type_.jump_ = 1;
			}
			break;

			case SDLK_s:
			{
				status_ = WAR1;
				input_type_.war1 = 1;
				UpdateImagePlayer(screen);

				fight = 1;
				cb_basic = 1;
				is_basic = 1;
				none_basic = 0;
				max_y = y_pos_;
				min_y = y_pos_ - 64 * 2;


			}
			break;
			case SDLK_q:
			{
				status_ = WAR2;
				input_type_.war2 = 1;
				UpdateImagePlayer(screen);
				is_basic = 0;
				fight = 1;
				if (on_ground_ == true)
				{

					max_y = y_pos_;
					min_y = y_pos_ - 64 * 2;

				}

				else
				{

					max_y = y_pos_ + 64 * 2;
					min_y = y_pos_ - 64 * 2;

				}
			}
			break;
			case SDLK_e:
			{
				status_ = WAR3;
				input_type_.war3 = 1;
				UpdateImagePlayer(screen);

				fight = 1;
				is_basic = 0;


				if (on_ground_ == true)
				{

					max_y = y_pos_;
					min_y = y_pos_ - 64 * 2;


				}
				else
				{


					max_y = y_pos_ + 64 * 2;
					min_y = y_pos_ - 64 * 2;

				}
			}




			break;

			case SDLK_w:
			{
				status_ = WAR4;
				input_type_.war4 = 1;
				UpdateImagePlayer(screen);

				fight = 1;

				unti = 1;

				
			}
			break;


			}
		}
		else if (events.type == SDL_KEYUP)
		{
			switch (events.key.keysym.sym) {

			case SDLK_v:
			{
				status_ = WALK_NONE;
				input_type_.right_ = 0;
				UpdateImagePlayer(screen);
				none_basic = 0;
				is_basic = 1;
			}
			break;
			case SDLK_c:
			{
				status_ = WALK_NONE;
				input_type_.left_ = 0;
				is_basic = 1;
				none_basic = 0;
				UpdateImagePlayer(screen);
			}
			break;
			case SDLK_s:
			{
				status_ = WALK_NONE;
				input_type_.war1 = 0;

				fight = 0;
				cb_basic = 0;
				min_y = 0;
				max_y = 0;
				is_basic = 1;
				UpdateImagePlayer(screen);

			}
			break;
			case SDLK_q:
			{

				status_ = WALK_NONE;
				fight = 0;
				
				max_y = 0;
				min_y = 0;
				is_basic = 1;
				UpdateImagePlayer(screen);

			}
			break;
			case SDLK_e:
			{
				status_ = WALK_NONE;
				fight = 0;
				input_type_.war3 = 0;
				max_y = 0;
				min_y = 0;
				is_basic = 1;
				UpdateImagePlayer(screen);
			}
			break;

			case SDLK_w:
			{

				status_ = WALK_NONE;
				fight = 0;
				input_type_.war4 = 0;
				max_y = 0;
				min_y = 0;
				
				
				UpdateImagePlayer(screen);

			}
			break;
			}
		}

	}
	else
	{
		if (events.type == SDL_KEYDOWN)
		{

			switch (events.key.keysym.sym)
			{

			case SDLK_RIGHT:
			{
				status_ = WALK_RIGHT;
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				cb_basic = 0;
				none_basic = 1;
				is_basic = 1;
				check = 1;
			
				UpdateImagePlayer(screen);
			}
			break;
			case SDLK_LEFT:
			{
				status_ = WALK_LEFT;

				input_type_.left_ = 1;
				input_type_.right_ = 0;
				cb_basic = 0;
				none_basic = 1;
				is_basic = 1;
				check = 0;
			
				UpdateImagePlayer(screen);
			}
			break;

			case SDLK_UP:
			{
				input_type_.jump_ = 1;
			}
			break;



			case SDLK_s:
			{
				status_ = WAR1;
				input_type_.war1 = 1;
				UpdateImagePlayer(screen);

				fight = 1;
				cb_basic = 1;
				is_basic = 1;
				none_basic = 0;
				max_y = y_pos_;
				min_y = y_pos_ - 64 * 2;


			}
			break;
			case SDLK_q:
			{
				status_ = WAR2;
				input_type_.war2 = 1;
				UpdateImagePlayer(screen);
				is_basic = 0;
				fight = 1;
				if (on_ground_ == true)
				{

					max_y = y_pos_;
					min_y = y_pos_ - 64 * 2;




				}






				else
				{





					max_y = y_pos_ + 64 * 2;
					min_y = y_pos_ - 64 * 2;







				}
			}
			break;
			case SDLK_e:
			{
				status_ = WAR3;
				input_type_.war3 = 1;
				UpdateImagePlayer(screen);

				fight = 1;
				is_basic = 0;


				if (on_ground_ == true)
				{

					max_y = y_pos_;
					min_y = y_pos_ - 64 * 2;

				}

				else
				{

					max_y = y_pos_ + 64 * 2;
					min_y = y_pos_ - 64 * 2;

				}
			}

			break;

			case SDLK_w:
			{
				status_ = WAR4;
				input_type_.war4 = 1;
				UpdateImagePlayer(screen);

				fight = 1;

				unti = 1;

			

			}

			}
		}
		else if (events.type == SDL_KEYUP)
		{
			switch (events.key.keysym.sym) {

			case SDLK_RIGHT:
			{
				status_ = WALK_NONE;
				input_type_.right_ = 0;
				is_basic = 1;
				none_basic = 0;
				UpdateImagePlayer(screen);
			}
			break;
			case SDLK_LEFT:
			{
				status_ = WALK_NONE;
				input_type_.left_ = 0;
				is_basic = 1;
				none_basic = 0;
				UpdateImagePlayer(screen);
			}
			break;
			case SDLK_s:
			{
				status_ = WALK_NONE;
				input_type_.war1 = 0;

				fight = 0;
				cb_basic = 0;
				min_y = 0;
				max_y = 0;
				UpdateImagePlayer(screen);

			}
			break;
			case SDLK_q:
			{

				status_ = WALK_NONE;
				fight = 0;
				
				max_y = 0;
				min_y = 0;
				is_basic = 1;
				UpdateImagePlayer(screen);

			}
			break;
			case SDLK_e:
			{
				status_ = WALK_NONE;
				fight = 0;
				input_type_.war3 = 0;
				max_y = 0;
				min_y = 0;
				is_basic = 1;
				UpdateImagePlayer(screen);
			}
			break;

			case SDLK_w:
			{

				status_ = WALK_NONE;
				fight = 0;
				input_type_.war4 = 0;
				max_y = 0;
				min_y = 0;

				UpdateImagePlayer(screen);

			}

			}
		}









		}





}



void MainObject::Doplayer(Map& map_data,SDL_Renderer* screen)
{
	
		x_val_ = 0;
		y_val_ += 0.8;
		if (y_val_ >= MAX_FALL_SPEED)
		{
			y_val_ = MAX_FALL_SPEED;
		}

		if (input_type_.left_ == 1)
		{
			x_val_ -= PLAYER_SPEED;
		}
		else if (input_type_.right_ == 1)
		{

			x_val_ += PLAYER_SPEED;
		}

		
		 if (input_type_.war2 == 1)
		{
			 if (swx > x_pos_)
			 {
				 if (time_move_skill == 0)
				 {
					 x_pos_ = (x_pos_ + swx) / 2;
					 y_pos_ = swy / 2;
					 time_move_skill = 1;
				 }
				 else
				 {
					 x_pos_ =  swx +64*2;
					 y_pos_ = swy ;
					 time_move_skill = 0;
					 input_type_.war2 = 0;
				 }
			}
			 else if (swx < x_pos_)
			 {
				 if (time_move_skill == 0)
				 {
					 x_pos_ = (x_pos_ + swx) / 2;
					 y_pos_ = swy / 2;
					 time_move_skill = 1;
				 }
				 else
				 {
					 x_pos_ = swx - 64 * 2;
					 y_pos_ = swy;
					 time_move_skill = 0;
					 input_type_.war2 = 0;
				 }
			 }
			
		}
		  
		else if (input_type_.war3 == 1) {
			 if (check == 1)
			 {
				 x_val_ += PLAYER_SPEED;
			 }
			 else
			 {
				 x_val_ -= PLAYER_SPEED;
			 }
		}
		
	
		else	if (input_type_.jump_ == 1)
		{

			if (on_ground_ == true)
			{
				y_val_ -= PLAYER_JUMP_VAL;
			}
			on_ground_ = false;
			input_type_.jump_ = 0;
		}

		 if (unti == 1)
		 {
			 time_unti++;
			 if (time_unti == 70)
			 {
				 time_unti = 0;
				 unti = 2;
			 }
		 }
		CheckToMap(map_data);
	CenterEntityOnMap(map_data);

	}

//refer from : https://phattrienphanmem123az.com/
void MainObject::CenterEntityOnMap(Map& map_data)
{
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
	if (map_data.start_x_ < 0)
	{
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;

	}
	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);
	if (map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
}

//refer from : https://phattrienphanmem123az.com/
void MainObject::CheckToMap(Map& map_data)
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

			
				if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
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

			
				if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
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
			
				if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
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

			
				if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
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


//refer from : https://phattrienphanmem123az.com/
void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
	
		if (status_ == WALK_LEFT)
		{

			LoadImg("img//player_run_left.png", des);
		}
		else if(status_==WALK_RIGHT)
		{
			LoadImg("img//player_run_right.png", des);
		}
		else if (status_ == WALK_NONE)
		{
			if (check == 0)  LoadImg("img//player_none_left.png", des);
			else LoadImg("img//player_none_right.png", des);

		}
		
		
		else if (status_ == WAR2)
		{
			if (check == 0)  LoadImg("img//war2_left1.png", des);
			else LoadImg("img//war2_right1.png", des);



		}
		else if (status_ == WAR3)
		{
			
			 LoadImg("img//war3_re.png", des);



		}
		else if (status_ == WAR1)
		{
			if (check == 0)  LoadImg("img//player_fight_left.png", des);
			else LoadImg("img//player_fight_right.png", des);
		}
	
}



