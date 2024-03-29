﻿#include "stdafx.h"
#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "TextObject.h"
#include "Music.h"
#include <string.h>
#include <vector>


#undef main
BaseObject g_background;
BaseObject g_background2;;
BaseObject star_game;

TTF_Font* font;
Music music_;




bool InitData() {

	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)  return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Ninja fight", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	

	if (g_window == NULL) {

		success = false;

	}
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) success = false;

		else {
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags)) success = false;
		}
	
		if (TTF_Init() == -1)
		{
			success = false;
		}
		
		font = TTF_OpenFont("font//lazy.ttf", 28);
		if (font == NULL)
		{
			success = false;
		}

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			return false;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			return false;
		}

	}
	return success;

}


bool LoadBackground() {
	bool ret = g_background.LoadImg("img//newbkgr4.jpg", g_screen);
	if (ret == false) return false;
	return true;
}


void close() {

	star_game.Free();
	g_background.Free();
	g_background2.Free();

	
	music_.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	TTF_CloseFont(font);
	atexit(SDL_Quit);
	atexit(Mix_Quit);
	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
}






int main(int arc, char* argv[]) 
{







	bool start = false;
	int pause=0;

	int x_;
	int y_;
	ImpTimer fps_timer;
	float vtrix;
	float vtriy;
	int tt;
	

	float vitribotx;
	float vitriboty;
	
	float max_y;
	float min_y;
	int myfight, botfight;



	if (InitData() == false) return -1;
	if (LoadBackground() == false) return -1;



	GameMap game_map;

	char file_name[20] = "map/map01.dat";
	game_map.LoadMap(file_name);

	game_map.LoadTiles(g_screen);


	MainObject p_player;
	p_player.LoadImg("img//player1_right.png", g_screen);
	p_player.set_clips();


	ThreatsObject p_threat;
	p_threat.LoadImg("img//bot_left.png",g_screen);
	p_threat.set_clips();

	

	int killed = 1000;
	int botkilled = 1000;

	TextObject p_myhp;
	p_myhp.set_xy(10, 10);

	TextObject p_bothp;
	p_bothp.set_xy(SCREEN_WIDTH -300, 10);

	int photo = 0;
	int lighting = 0;

	BulletObject p_bullet;

		p_bullet.LoadImg("img//war3_right1.png", g_screen);
		p_bullet.set_clips();
	
	
	bool is_quit = false;

	while (!is_quit)
	{
		fps_timer.start();
		
		while (SDL_PollEvent(&g_event) != 0) {


			if (g_event.type == SDL_QUIT) {

				is_quit = true;

			}
			else if (g_event.type == SDL_KEYDOWN)
			{
				if (g_event.key.keysym.sym == SDLK_SPACE)
				{
					pause = 1;
				}
			}
			
			else if (g_event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (g_event.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&x_, &y_);
				}
			}
			p_player.HandelInputAction(g_event, g_screen);
		}
		if (!start)
		{

			if (photo <=3)
			{
				photo++;
				
					if (photo ==1) 
					{
						
						star_game.LoadImg("video//start_game2_000.bmp", g_screen);
						star_game.Render(g_screen, NULL);
						
					}
				else if (photo==2)
				{
					
					star_game.LoadImg("video//start_game2_007.bmp", g_screen);
					star_game.Render(g_screen, NULL);
					
				}
				else if (photo ==3)
				{
					
					star_game.LoadImg("video//start_game2_009.bmp",  g_screen);
					star_game.Render(g_screen, NULL);

					SDL_Delay(1000);
				}
			

					SDL_Delay(2000);
				
			
			}
			else
			{

				
				music_.LoadMusic("music//start_game.mp3");
				music_.DisplayMusic(0);
				music_.Volume(MAX_VOLUME / 2);
				g_background2.LoadImg("img//tachi.jpg", g_screen);
				g_background2.Render(g_screen, NULL);

				TextObject begin;
				begin.set_xy(SCREEN_WIDTH / 2 - 64 * 2, SCREEN_HEIGHT / 2 + 64 * 2);
				begin.RenderText("START GAME", font, g_screen, 0);

				if (Impact::Impact_(x_, y_, begin.get_Rect())) start = true;
				x_ = 0; y_ = 0;
			}
		}
		else if (start)
		{
			music_.stopMusic();


		
			if (pause == 2)
			{
				if (botkilled <killed)

				{
					g_background2.LoadImg("img//wingame.jpg", g_screen);
					g_background2.SetRect(0,0);
					g_background2.Render(g_screen, NULL);
				}
				else if (killed <botkilled)
				{
					g_background2.LoadImg("img//lose_game.jpg", g_screen);
					g_background2.SetRect(0, 0);
					g_background2.Render(g_screen, NULL);
				}
				TextObject endgame[2];
				endgame[0].set_xy(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 64 +32);
				endgame[0].RenderText("CONTINUTE PLAY", font, g_screen, 0);

				endgame[1].set_xy(SCREEN_WIDTH / 2-64*3, SCREEN_HEIGHT / 2 + 64+32 );
				endgame[1].RenderText("EXIT GAME", font, g_screen, 0);
				
				for (int i = 0; i < 2; i++)
				{
					if (Impact::Impact_(x_, y_, endgame[i].get_Rect()))
					{
						if (i == 0) { start = false; pause = 0; killed = 1000; botkilled = 1000; p_player.set_vt(0, 0); p_threat.set_vt(SCREEN_WIDTH, 0); }
						else if (i == 1)
						{

							if (MessageBox(NULL, L"EXITED THE GAME ", L"GAME OVER", MB_OK | MB_ICONSTOP) == IDOK)
							{

								p_player.Free();
								p_threat.Free();
								close();
								SDL_Quit();
								return 0;
							}

						}
					}

				}


			}

		else  if (pause == 1)
			{




				g_background2.LoadImg("img//s9.jpg", g_screen);
				g_background2.SetRect(272, 113);
				g_background2.Render(g_screen, NULL);

				TextObject choose[2];
				choose[0].set_xy(SCREEN_WIDTH / 2 - 64, SCREEN_HEIGHT / 2 - 64);
				choose[0].RenderText("Resume", font, g_screen, 1);

				choose[1].set_xy(SCREEN_WIDTH / 2 - 64, SCREEN_HEIGHT / 2);
				choose[1].RenderText("Exit", font, g_screen, 1);

				 
				for (int i = 0; i < 2; i++)
				{
					if (Impact::Impact_(x_, y_, choose[i].get_Rect()))
					{
						if (i == 0) pause = 0;
						else if (i == 1)
						{
							if (MessageBox(NULL, L"EXITED THE GAME ", L"GAME OVER", MB_OK | MB_ICONSTOP) == IDOK)
							{

								p_player.Free();
								p_threat.Free();
								close();
								SDL_Quit();
								return 0;
							}
						}

					}
				}
				x_ = 0, y_ = 0;
			}
			else if(pause==0)
			{
				
			
				SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
				SDL_RenderClear(g_screen);

				g_background.Render(g_screen, NULL);



				Map map_data = game_map.getMap();

				lighting = p_player.sent_lighting();


				vtrix = p_player.vitri_x();
				vtriy = p_player.vitri_y();
				tt = p_player.set_check();
				myfight = p_player.set_fight();
				max_y = p_player.sent_max_y();
				min_y = p_player.sent_min_y();


				vitribotx = p_threat.get_x_pos();
				vitriboty = p_threat.get_y_pos();
				botfight = p_threat.sent_fight();

				p_player.Swap(vitribotx, vitriboty);

				p_player.SetMapXY(map_data.start_x_, map_data.start_y_);

				p_player.Doplayer(map_data,g_screen);

				p_player.Show(g_screen);

				game_map.SetMap(map_data);

				game_map.DrawMap(g_screen);





				p_threat.SetMapXY(map_data.start_x_, map_data.start_y_);
				p_threat.ktraN(vtrix, vtriy, tt);


				p_threat.ImpMoveType(g_screen);
				p_threat.DoPlayer(map_data);



				p_threat.Show(g_screen);

				SDL_Rect rect_player = p_player.GetRectFrame();
				SDL_Rect rect_bullet = p_bullet.GetRectFrame();
				if (lighting == 1)
				{
					
					
						p_bullet.SetMapXY(map_data.start_x_, map_data.start_y_);
						p_bullet.DoPlayer(map_data);
						p_bullet.GPS(vitribotx);
						p_bullet.Show(g_screen);
						
					
				
				}

				if (Impact::Impact_(vitribotx, vitriboty, rect_bullet)) botkilled -= 5;
				
				bool bCol1 = false;
				bool bCol2 = false;
				bool bCol3 = false;



				if (myfight == 1 && botfight == 0)
				{

					if (vitribotx <= vtrix + 64 * 2 && vitribotx >= vtrix - 64 * 2 && vitriboty <= max_y && vitriboty >= min_y) bCol1 = true;






				}

				else if (botfight == 1 && myfight == 0)
				{

					if (vtrix >= vitribotx - 64 * 2 && vtrix <= vitribotx + 64 * 2 && vtrix >= vitriboty - 64 * 2 && vtriy <= vitriboty + 64 * 2) bCol2 = true;


				}

				else
				{
					if (vitribotx <= vtrix + 64 && vitribotx >= vtrix - 64 && vitriboty <= max_y && vitriboty >= min_y) bCol3 = true;
					if (vtrix >= vitribotx - 64 && vtrix <= vitribotx + 64 && vtrix >= vitriboty - 64 && vtriy <= vitriboty + 64) bCol3 = true;


				}


				if (bCol3)
				{
					if (p_player.set_check() == 1)
					{
						p_player.set_xpos(vtrix - 64 * 2);
						p_threat.set_x_pos(vitribotx + 64 * 2);
					}
					else
					{
						p_player.set_xpos(vtrix + 64 * 2);
						p_threat.set_x_pos(vitribotx - 64 * 2);

					}

				}





			
				else if (bCol1)
				{
					
					botkilled -= 10;
					



				}
				
				else if (bCol2)
				{
					killed -= 10;

				
				}

				if (killed <= 0||botkilled<=0)
				{
					pause = 2;
				}
				char myhp[20];

				snprintf(myhp, 20, "MY HP : %d", killed);
				p_myhp.RenderText(myhp, font, g_screen, 0);

				


				char bothp[20];

				snprintf(bothp, 20, "BOT HP : %d", botkilled);
				p_bothp.RenderText(bothp, font, g_screen, 0);
			}
		}
			SDL_RenderPresent(g_screen);

			int  real_imp_time = fps_timer.get_ticks();

			int time_one_frame = 1000 / FRAME_PER_SECOND;

			if (real_imp_time < time_one_frame)
			{
				int delay_time = time_one_frame - real_imp_time;
				if (delay_time >= 0)
					SDL_Delay(delay_time);
			}

		
   }


p_myhp.free();
p_bothp.free();
p_player.Free();

	close();
	return 0;
}