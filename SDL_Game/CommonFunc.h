#pragma once

#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <string>
#include <vector>
#include <SDL.h>

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>



static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;


// Screen

const int  FRAME_PER_SECOND = 25;



const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 64;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;






#define BLANK_TILE 0


#define TILE_SIZE 64

#define MAX_MAP_X 22
#define MAX_MAP_Y 10


#define MAX_VOLUME 128
#define BULLET_SPEED 5

typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
	int up_left_;
	int up_right_;
	int war1;
	int war2;
	int war3r;
	int war3l;

	


};

typedef struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];

	char* file_name_;


};

namespace Impact
{
	bool Impact_(const int& x, const int& y, SDL_Rect rect);

}


#endif 

