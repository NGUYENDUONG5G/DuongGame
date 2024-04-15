#include "stdafx.h"
#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "Player2.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "TextObject.h"
#include "Music.h"
#include <string.h>
#include <vector>
#include "Sound.h"
#include<iostream>
#include<vector>
#include<random>

#undef main
BaseObject g_background;
BaseObject g_background2;
BaseObject g_background3;
BaseObject star_game;
BaseObject cancel;
BaseObject key_star;
BaseObject key_end;
BaseObject key_resume;
BaseObject key_exit;
BaseObject key_open_music;
BaseObject key_close_music;
BaseObject key_go;
BaseObject hp_me;
BaseObject hp_bot;
BaseObject vs_bot_, vs_1_;
BaseObject skill1,skill2,skill3;
BaseObject skill1_1, skill2_1, skill3_1;
Music music_star;
Music music_bkgr;
Sound boxing;
Sound knife;
Sound axe;
Sound is_killed;

TTF_Font* font;

std::string bkgr[4] = {"img//newbkgr0.jpg","img//newbkgr1.jpg","img//newbkgr2.gif","img//newbkgr3.jpg"};


bool InitData() {

	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO|| SDL_INIT_AUDIO);  // Khởi tạo thư viện SDL2
	if (ret < 0)  return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); //cài đặt các tính năng của thư viện
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

		
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			return false;
		}

	}
	return success;

}


bool LoadBackground(int choose_bkgr) {
	bool ret = g_background.LoadImg(bkgr[choose_bkgr], g_screen);
	if (ret == false) return false;
	return true;
}





void close() {

	star_game.Free();
	g_background.Free();
	g_background2.Free();
	g_background3.Free();
	star_game.Free();
	cancel.Free();
	music_bkgr.Free();
	music_star.Free();

	 boxing.DisplayMusic();
	 knife.Free();
	 axe.Free();
	 is_killed.Free();
	 vs_bot_.Free();
	 vs_1_.Free();
	 skill1.Free();
	 skill2.Free();
	 skill3.Free();
	 skill1_1.Free();
	 skill2_1.Free();
	 skill3_1.Free();
	 key_star.Free();
	 key_end.Free();
	 key_resume.Free();
	 key_exit.Free();
	 key_open_music.Free();
	 key_close_music.Free();
	 key_go.Free();
	 hp_me.Free();
	 hp_bot.Free();

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

	srand(time(NULL));
	
	int choose_bkgr = 0;


	
	bool start = false;
	bool enter = false;
	bool click = false;
	bool state_mus = false; 
	int pause=0;
	int pk = 2;

	int x_;
	int y_;
	ImpTimer fps_timer;
	float vtrix;
	float vtriy;
	int tt;
	

	float vitribotx;
	float vitriboty;
	
	
	int myfight, botfight;


	int player2_fight;

	
	float vtrix2, vtriy2;


	if (InitData() == false) return -1;
	



	GameMap game_map;

	char file_name[20] = "map/map01.dat";
	game_map.LoadMap(file_name);

	game_map.LoadTiles(g_screen);


	MainObject p_player;
	p_player.LoadImg("img//player_none_right.png", g_screen);
	p_player.set_clips();

	Player2 p_player2;
	p_player2.LoadImg("img//player2_none_left.png", g_screen);
	p_player2.set_clips();

	ThreatsObject p_threat;
	p_threat.LoadImg("img//bot_none_left.png",g_screen);
	p_threat.set_clips();
	p_threat.set_bots();

	

	float killed = 1000;
	float botkilled = 1000;
	float real_hp_me = 1000;
	float real_hp_bot = 1000;
	

	TextObject begin;
	TextObject endgame[2];
	TextObject choose[2];
	TextObject ready;
	TextObject count_match, count_player;
	count_match.set_xy(SCREEN_WIDTH / 2 - 40, 10);
	count_player.set_xy(SCREEN_WIDTH / 2 , 10);

	TextObject vs_bot;
	TextObject vs_1;
	TextObject tutorial_player1, tutorial_player2;


	
	BulletObject p_bullet;
	p_bullet.set_system_basis();
	BulletObject p_bullet2;
	p_bullet2.set_system_basis();
	BulletObject p_unti;
	BulletObject p_unti2;

	int photo = 0;
	int basic_skill = 0;
	int basic_skill2 = 0;
	int dame_me = 10;
	int dame_bot = 10;
	int match = 0;
	int match_pk = 0;
	
	bool mus_star = false;
	music_star.LoadMusic("music//star_game.mp3");
	bool mus_bkgr = false;
	music_bkgr.LoadMusic("music//fight_game.mp3");

	boxing.LoadMusic("music//boxing.mp3");
	knife.LoadMusic("music//knife.mp3");
	axe.LoadMusic("music//axe.mp3");
	is_killed.LoadMusic("music//killed.mp3");




	bool is_quit = false;

	while (!is_quit)
	{
		fps_timer.start();
		
		while (SDL_PollEvent(&g_event) != 0)
		{


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
			p_player.HandelInputAction(g_event, g_screen,pk);
			p_player2.HandelInputAction(g_event, g_screen);
		}
		if (!start)
		{

			if (photo <= 3)
			{
				photo++;

				if (photo == 1)
				{

					star_game.LoadImg("img//logo_game.jpg", g_screen);
					star_game.Render(g_screen, NULL);

				}
				else if (photo == 2)
				{

					star_game.LoadImg("img//white_gr.png", g_screen);
					star_game.Render(g_screen, NULL);

				}
				else if (photo == 3)
				{

					star_game.LoadImg("img//bkgr_menu.jpg", g_screen);
					star_game.Render(g_screen, NULL);

					SDL_Delay(1000);

				}


				SDL_Delay(2000);


			}
			else
			{
				if (mus_star == false)
				{
					music_star.DisplayMusic();
					music_star.Volume(MAX_VOLUME / 2);
					mus_star = true;
				}


				if (!enter)
				{

					g_background2.LoadImg("img//bkgr_menu.jpg", g_screen);
					g_background2.Render(g_screen, NULL);

					key_star.LoadImg("img//key.png", g_screen);
					key_star.SetRect(SCREEN_WIDTH / 2 - 64 * 3, SCREEN_HEIGHT / 2 + 64 + 30);
					key_star.Render(g_screen, NULL);

					begin.set_xy(SCREEN_WIDTH / 2 - 64 * 2, SCREEN_HEIGHT / 2 + 64 * 2);
					begin.RenderText("START GAME", font, g_screen, 1);


					if (Impact::Impact_(x_, y_, begin.get_Rect()))

					{
						enter = true;
						key_star.LoadImg("img//key_small.png", g_screen);
						key_star.SetRect(SCREEN_WIDTH / 2 - 64 * 3 + 20, SCREEN_HEIGHT / 2 + 64 + 30);
						key_star.Render(g_screen, NULL);


					}
				}
				else if (enter)
				{

					g_background3.LoadImg("img//bkgr_menu2.jpg", g_screen);
					g_background3.SetRect(85, 0);
					g_background3.Render(g_screen, NULL);

					if (pk == 2)
					{


						vs_bot_.LoadImg("img//key_big.png", g_screen);
						vs_bot_.SetRect(SCREEN_WIDTH / 2 - 450, SCREEN_HEIGHT / 2 - 60);
						vs_bot_.Render(g_screen, NULL);

						vs_1_.LoadImg("img//key_big.png", g_screen);
						vs_1_.SetRect(SCREEN_WIDTH / 2+20 , SCREEN_HEIGHT / 2 - 60);
						vs_1_.Render(g_screen, NULL);

						vs_bot.set_xy(SCREEN_WIDTH / 2 - 360, SCREEN_HEIGHT / 2);
						vs_bot.RenderText("WAR WITH BOT ", font, g_screen, 1);

						vs_1.set_xy(SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT / 2);
						vs_1.RenderText("WAR WITH HUMAN ", font, g_screen, 1);

						if (Impact::Impact_(x_, y_, vs_bot_.GetRect())) pk = 0;
						else if (Impact::Impact_(x_, y_, vs_1_.GetRect())) pk = 1; 
						std::cout << " PK = " << pk << '\n';
					}
					else if (pk != 2)
					{
						cancel.LoadImg("img//cancel.png", g_screen);
						cancel.SetRect(20, 20);
						cancel.Render(g_screen, NULL);


						key_go.LoadImg("img//key.png", g_screen);
						key_go.SetRect(SCREEN_WIDTH / 2 - 148, 450);
						key_go.Render(g_screen, NULL);



						ready.set_xy(SCREEN_WIDTH / 2 - 20, 480);
						ready.RenderText("GO", font, g_screen, 1);

						if (pk == 1)
						{
							tutorial_player1.set_xy(SCREEN_WIDTH / 2 - 320, SCREEN_HEIGHT / 2 + 100);
							tutorial_player1.RenderText("PLAYER 1 ", font, g_screen, 1);

							tutorial_player2.set_xy(SCREEN_WIDTH / 2 + 320, SCREEN_HEIGHT / 2 + 100);
							tutorial_player2.RenderText("PLAYER 2 ", font, g_screen, 1);
						}
						if (!click)
						{
							skill1.LoadImg("img//axe_before.png", g_screen);
							skill1.SetRect(100, 30);
							skill1.Render(g_screen, NULL);
							skill2.LoadImg("img//knife_before.png", g_screen);
							skill2.SetRect(173, 30);
							skill2.Render(g_screen, NULL);
							skill3.LoadImg("img//knife2_before.png", g_screen);
							skill3.SetRect(246, 30);
							skill3.Render(g_screen, NULL);

							if (pk == 1)
							{
								skill1_1.LoadImg("img//axe_before.png", g_screen);
								skill1_1.SetRect(962, 30);
								skill1_1.Render(g_screen, NULL);
								skill2_1.LoadImg("img//knife_before.png", g_screen);
								skill2_1.SetRect(1034, 30);
								skill2_1.Render(g_screen, NULL);
								skill3_1.LoadImg("img//knife2_before.png", g_screen);
								skill3_1.SetRect(1107, 30);
								skill3_1.Render(g_screen, NULL);
							}
							if (x_ <= 1280 && x_ >= 0 && y_ >= 0 && y_ <= 640) click = true;
						}
						else
						{

						


							if (Impact::Impact_(x_, y_, skill1.GetRect()))
							{
								skill1.LoadImg("img//axe_after.jpg", g_screen);
								skill2.LoadImg("img//knife_before.png", g_screen);
								skill3.LoadImg("img//knife2_before.png", g_screen);
								basic_skill = 1;
							}
							else if (Impact::Impact_(x_, y_, skill2.GetRect()))
							{
								skill1.LoadImg("img//axe_before.png", g_screen);
								skill2.LoadImg("img//knife_after.png", g_screen);
								skill3.LoadImg("img//knife2_before.png", g_screen);
								basic_skill = 2;
							}
							else if (Impact::Impact_(x_, y_, skill3.GetRect()))
							{
								skill1.LoadImg("img//axe_before.png", g_screen);
								skill2.LoadImg("img//knife_before.png", g_screen);
								skill3.LoadImg("img//knife2_after.png", g_screen);
								basic_skill = 3;
							}


							if (pk == 1)

							{
								if (Impact::Impact_(x_, y_, skill1_1.GetRect()))
								{
									skill1_1.LoadImg("img//axe_after.jpg", g_screen);
									skill2_1.LoadImg("img//knife_before.png", g_screen);
									skill3_1.LoadImg("img//knife2_before.png", g_screen);
									basic_skill2 = 1;
								}
								else if (Impact::Impact_(x_, y_, skill2_1.GetRect()))
								{
									skill1_1.LoadImg("img//axe_before.png", g_screen);
									skill2_1.LoadImg("img//knife_after.png", g_screen);
									skill3_1.LoadImg("img//knife2_before.png", g_screen);
									basic_skill2 = 2;
								}
								else if (Impact::Impact_(x_, y_, skill3_1.GetRect()))
								{
									skill1_1.LoadImg("img//axe_before.png", g_screen);
									skill2_1.LoadImg("img//knife_before.png", g_screen);
									skill3_1.LoadImg("img//knife2_after.png", g_screen);
									basic_skill2 = 3;
								}

								skill1_1.SetRect(962, 30);
								skill1_1.Render(g_screen, NULL);
								skill2_1.SetRect(1034, 30);
								skill2_1.Render(g_screen, NULL);
								skill3_1.SetRect(1107, 30);
								skill3_1.Render(g_screen, NULL);


							}
							std::cout << basic_skill << '\n';
							skill1.SetRect(100, 30);
							skill1.Render(g_screen, NULL);
							skill2.SetRect(173, 30);
							skill2.Render(g_screen, NULL);
							skill3.SetRect(246, 30);
							skill3.Render(g_screen, NULL);

						}
						if (Impact::Impact_(x_, y_, ready.get_Rect())) start = true;
						else if (Impact::Impact_(x_, y_, cancel.GetRect())) pk = 2;
					}
					
				}
			}

		
			
				
			
		}
		else if (start)
		{
		
		
			if (LoadBackground(choose_bkgr) == false) is_quit = true;
			if (mus_bkgr == false)
			{
				music_bkgr.DisplayMusic();
				music_bkgr.Volume(MAX_VOLUME / 2);
				mus_bkgr = true;
				state_mus = true;
			}

			if (pause == 2)
			{
				if (botkilled <killed)

				{
					
					SDL_Delay(1000);
					int save = choose_bkgr;
					while ( choose_bkgr==save)
					{
						choose_bkgr = rand() % 4;
					}

					if (pk == 0)
					{
						pause = 0;
						killed = 1000; botkilled += 1000;
						real_hp_me = 1000;
						real_hp_bot = botkilled;
						p_player.set_vt(0, 0); p_threat.set_vt(SCREEN_WIDTH, 0);
						dame_bot += 10;
						match++;
					}
					else if (pk == 1)
					{
						match++;
						if (match < 4)
						{
							pause = 0;
							p_player.set_vt(0, 0);
							p_player2.set_vt(SCREEN_WIDTH, 0);
							killed = 1000;
							botkilled = 1000;
						}
						else 
						{

							g_background2.LoadImg("img//win_black.jpg", g_screen);
							g_background2.SetRect(320, 0);
							g_background2.Render(g_screen, NULL);

							if (x_ <= 1280 && x_ > 0 && y_ > 0 && y_ <= 640) { start = false; pk = 2; match = 0; match_pk = 0; }
						}
					}
				}
				else if (killed < botkilled)
				{
					if (pk == 0)
					{
						g_background2.LoadImg("img//lose_game.jpg", g_screen);
						g_background2.SetRect(250, 0);
						g_background2.Render(g_screen, NULL);
						match = 0;

						endgame[0].set_xy(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 64 + 32);
						endgame[0].RenderText("CONTINUTE PLAY", font, g_screen, 1);

						endgame[1].set_xy(SCREEN_WIDTH / 2 - 64 * 3, SCREEN_HEIGHT / 2 + 64 + 32);
						endgame[1].RenderText("EXIT GAME", font, g_screen, 1);

						for (int i = 0; i < 2; i++)
						{
							if (Impact::Impact_(x_, y_, endgame[i].get_Rect()))
							{
								if (i == 0) {
									start = false;
									pause = 0; killed = 1000;
									botkilled = 1000;
									p_player.set_vt(0, 0);
									p_threat.set_vt(SCREEN_WIDTH, 0);
									choose_bkgr = 0;
									dame_me = 10; dame_bot = 10;
									mus_star = false;
									mus_bkgr = false;
								}
								else if (i == 1)
								{
									is_quit=true;
								}
							}

						}
					}
					else if (pk == 1)
					{
						match_pk++;
						if (match_pk < 4)
						{
							pause = 0;
							p_player.set_vt(0, 0);
							p_player2.set_vt(SCREEN_WIDTH, 0);
							killed = 1000;
							botkilled = 1000;

						}

						else  {
							

							g_background2.LoadImg("img//win_green.jpg", g_screen);
							g_background2.SetRect(320, 0);
							
							g_background2.Render(g_screen, NULL);

							if (x_ <= 1280 && x_ > 0 && y_ > 0 && y_ <= 640) { start = false; pk = 2; match = 0; match_pk = 0; }
						}
					



						
					}
				}

			}

		else  if (pause == 1)
			{




				g_background2.LoadImg("img//s9.jpg", g_screen);
				g_background2.SetRect(272, 113);
				g_background2.Render(g_screen, NULL);

				key_resume.LoadImg("img//key_small.png", g_screen);
				key_resume.SetRect(SCREEN_WIDTH / 2 +64, SCREEN_HEIGHT / 2 -20);
				key_resume.Render(g_screen, NULL);

				key_exit.LoadImg("img//key_small.png", g_screen);
				key_exit.SetRect(SCREEN_WIDTH / 2 - 64*4, SCREEN_HEIGHT / 2-20);
				key_exit.Render(g_screen, NULL);
			
				if (state_mus)
				{
					music_bkgr.resumeMusic();
					key_open_music.LoadImg("img//open_volume.png", g_screen);
					key_open_music.SetRect(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 60);
					key_open_music.Render(g_screen, NULL);
					if(Impact::Impact_(x_,y_,key_open_music.GetRect())) state_mus=false;
				}
				else
				{
					music_bkgr.stopMusic();
					key_close_music.LoadImg("img//close_volume.png", g_screen);
					key_close_music.SetRect(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 60);
					key_close_music.Render(g_screen, NULL);
					if (Impact::Impact_(x_, y_, key_close_music.GetRect())) state_mus = true;


				}

				choose[0].set_xy(SCREEN_WIDTH / 2 +64*2, SCREEN_HEIGHT / 2 );
				choose[0].RenderText("Resume", font, g_screen, 1);

				choose[1].set_xy(SCREEN_WIDTH / 2 - 64*2-30, SCREEN_HEIGHT / 2);
				choose[1].RenderText("Exit", font, g_screen, 1);

				 
				for (int i = 0; i < 2; i++)
				{
					if (Impact::Impact_(x_, y_, choose[i].get_Rect()))
					{
						if (i == 0) pause = 0;
						else if (i == 1)
						{
							is_quit = true;
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

			
				int is_basic;
				int is_basic2;

				bool bCol1 = false;
				bool bCol2 = false;
				bool bCol3 = false;

				vtrix = p_player.vitri_x();
				vtriy = p_player.vitri_y();
				tt = p_player.set_check();
				myfight = p_player.set_fight();
				
				int cb_basic = p_player.cb_basic_();
				is_basic = p_player.is_basic_();
				int unti = p_player.sent_unti();
				



				
			


				p_player.Swap(vitribotx, vitriboty);

				p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
				
				p_player.Doplayer(map_data,g_screen);

				p_player.Show(g_screen);


				
			
				game_map.SetMap(map_data);

				game_map.DrawMap(g_screen);
				SDL_Rect rect_player = p_player.GetRectFrame();

				

				if (is_basic == 1) // cho phép hiện đánh thường
				{
					
					p_bullet.set_basic_skill(basic_skill);
					p_bullet.set_tt(tt);
					p_bullet.set_cb_basic(cb_basic);
					p_bullet.Loadac(g_screen);
					
					

					if (tt == 1)
					{
						p_bullet.SetRect(rect_player.x, rect_player.y - 20);
					}
					else
					{
						p_bullet.SetRect(rect_player.x - 20, rect_player.y - 20);

					}
					p_bullet.action(g_screen,60);
					if (basic_skill == 0) dame_me = 10;
					else if (basic_skill == 1) dame_me = 15;
					else if (basic_skill == 2) dame_me = 20;
					else if (basic_skill == 3) dame_me = 30;
				}


				

				if (pk == 1)
				{
					vtrix2 = p_player2.vitri_x();
					vtriy2 = p_player2.vitri_y();

					player2_fight = p_player2.set_fight();
					int tt2 = p_player2.set_check();
					
					int cb_basic2 = p_player2.cb_basic_();
					is_basic2 = p_player2.is_basic_();
					int unti2 = p_player2.sent_unti();

					p_player2.SetMapXY(map_data.start_x_, map_data.start_y_);

					p_player2.Doplayer(map_data, g_screen);

					p_player2.Show(g_screen);

					SDL_Rect rect_player2 = p_player2.GetRect();

					if (is_basic2 == 1) // cho phép hiện đánh thường
					{

						p_bullet2.set_basic_skill(basic_skill2);
						p_bullet2.set_tt(tt2);
						p_bullet2.set_cb_basic(cb_basic2);
						p_bullet2.Loadac(g_screen);



						if (tt2 == 1)
						{
							p_bullet2.SetRect(rect_player2.x, rect_player2.y - 20);
						}
						else
						{
							p_bullet2.SetRect(rect_player2.x - 20, rect_player2.y - 20);

						}
						p_bullet2.action(g_screen, 60);
						if (basic_skill2 == 0) {
							dame_bot = 10; 
						}
						else if (basic_skill2 == 1) {
							dame_bot = 15; 
						}
						else if (basic_skill2 == 2) {
							dame_bot = 20; 
						}
						else if (basic_skill2 == 3) {
							dame_bot = 30;
						}

					}
					if (player2_fight == 1)
					{
						if (basic_skill2 == 0) {
							boxing.DisplayMusic();
						}
						else if (basic_skill2 == 1) {
							axe.DisplayMusic();
						}
						else if (basic_skill2 == 2||basic_skill2==3) {
							knife.DisplayMusic();
						}
					

					}

					if (unti2 != 2)// Chiêu cuối 
					{
						p_unti2.set_unti(unti2);
						p_unti2.Loadac(g_screen);
						p_unti2.SetRect(rect_player2.x - 64, rect_player2.y - 100);
						p_unti2.action(g_screen, 180);

						if (Impact::Impact_(vtrix, vtriy, p_unti2.GetRect())) killed -= 20;

					}

					if (myfight == 1 && player2_fight == 0)
					{

						if (vtrix2 <= vtrix + 64 * 2 && vtrix2 >= vtrix - 64 * 2 && vtriy2 <= vtriy+64*2 && vtriy2 >= vtriy-64*2) bCol1 = true;


					}
					 
					else if (player2_fight == 1 && myfight == 0)
					{

						if (vtrix >= vtrix2 - 64 * 2 && vtrix <= vtrix2 + 64 * 2 && vtriy >= vtriy2-64*2 && vtriy <= vtriy2+64*2) bCol2 = true;


					}

					else if (myfight == 1 && player2_fight == 1)
					{
						if (vtrix2 <= vtrix + 64 * 2 && vtrix2 >= vtrix - 64 * 2 && vtriy2 <= vtriy + 64 * 2 && vtriy2 >= vtriy - 64 * 2)  bCol3 = true;

						else 	if (vtrix >= vtrix2 - 64 * 2 && vtrix <= vtrix2 + 64 * 2 && vtriy >= vtriy2 - 64 * 2 && vtriy <= vtriy2 + 64 * 2)  bCol3 = true;


					}
			}
				else if (pk == 0)
				{
					vitribotx = p_threat.get_x_pos();
					vitriboty = p_threat.get_y_pos();
					botfight = p_threat.sent_fight();


					p_threat.set_choose_bot(choose_bkgr);
					p_threat.SetMapXY(map_data.start_x_, map_data.start_y_);
					p_threat.ktraN(vtrix, vtriy, tt);
					p_threat.RandomAction();

					p_threat.ImpMoveType(g_screen);
					p_threat.DoPlayer(map_data);





					p_threat.Show(g_screen);


					if (myfight == 1 && botfight == 0)
					{

						if (vitribotx <= vtrix + 64 * 2 && vitribotx >= vtrix - 64 * 2 && vitriboty <= vtriy+64*2 && vitriboty >= vtriy-64*2) bCol1 = true;


					}

					else if (botfight == 1 && myfight == 0)
					{

						if (vtrix >= vitribotx - 64 * 2 && vtrix <= vitribotx + 64 * 2 && vtriy >= vitriboty - 64 * 2 && vtriy <= vitriboty + 64 * 2) bCol2 = true;

						std::cout << bCol2 << '\n';
					}
					else if (myfight == 1 && botfight == 1)
					{
						if (vitribotx <= vtrix + 64 * 2 && vitribotx >= vtrix - 64 * 2 && vitriboty <= vtriy + 64 * 2 && vitriboty >= vtriy - 64 * 2) bCol3 = true;

						else 	if (vtrix >= vitribotx - 64 && vtrix <= vitribotx + 64 && vtriy >= vitriboty - 64 && vtriy <= vitriboty + 64) bCol3 = true;


					}
				}
			
				

				
				
				
				if (unti != 2)// Chiêu cuối 
				{
					p_unti.set_unti(unti);
					p_unti.Loadac(g_screen);
					p_unti.SetRect(rect_player.x - 64, rect_player.y - 100);
					p_unti.action(g_screen, 180);
					if (pk == 0)
					{
						if (Impact::Impact_(vitribotx,vitriboty, p_unti.GetRect())) botkilled -= 20;
					}
					else if (pk == 1)
					{

						if (Impact::Impact_(vtrix2, vtriy2, p_unti.GetRect())) botkilled -= 20;
					}
				}

				


				
				
				if (myfight == 1)
				{
					if (basic_skill == 0) boxing.DisplayMusic();
					else if (basic_skill == 1) axe.DisplayMusic();
					else if (basic_skill == 2||basic_skill==3) knife.DisplayMusic();
				}


				if (bCol3)
				{
						if (p_player.set_check() == 1)
						{
							p_player.set_xpos(vtrix - 64 * 2);
							if (pk == 0) p_threat.set_x_pos(vitribotx + 64 * 2);
							else if (pk == 1) p_player2.set_xpos(vtrix+64*2);
							
						}
						else
						{
							p_player.set_xpos(vtrix + 64 * 2);
							if (pk == 0) p_threat.set_x_pos(vitribotx - 64 * 2);
							else if (pk == 1) p_player2.set_xpos(vtrix - 64 * 2);

						}
					
					
				}
			
				else if (bCol1)
				{
					
					botkilled -= dame_me;
					
				}
				
				else if (bCol2)
				{
					killed -= dame_bot;
					is_killed.DisplayMusic();
				
				}

				if (killed <= 0||botkilled<=0)
				{
					pause = 2;
				}
				
				if (killed > real_hp_me*4/5)
				{
					hp_me.LoadImg("img//full_hp.png", g_screen);

				}
				else if (killed > real_hp_me*3/5)
				{
					hp_me.LoadImg("img//four_of_five.png", g_screen);
				}
				else if (killed > real_hp_me*2.5)
				{
					hp_me.LoadImg("img//three_of_five.png", g_screen);
				}
				else if (killed > real_hp_me/5)
				{
					hp_me.LoadImg("img//two_of_five.png", g_screen);
				}
				else hp_me.LoadImg("img//one_of_five.png", g_screen);

				hp_me.SetRect(10, 10);
				hp_me.Render(g_screen, NULL);


				if (botkilled > real_hp_bot*4/5)
				{
					hp_bot.LoadImg("img//full_hp.png", g_screen);

				}
				else if (botkilled > real_hp_bot*3/5)
				{
					hp_bot.LoadImg("img//four_of_five_bot.png", g_screen);
				}
				else if (botkilled > real_hp_bot*2/5)
				{
					hp_bot.LoadImg("img//three_of_five_bot.png", g_screen);
				}
				else if (botkilled > real_hp_bot/5)
				{
					hp_bot.LoadImg("img//two_of_five_bot.png", g_screen);
				}
				else hp_bot.LoadImg("img//one_of_five_bot.png", g_screen);

				hp_bot.SetRect(SCREEN_WIDTH-250, 10);
				hp_bot.Render(g_screen, NULL);
				if (pk == 0)
				{
					char smatch[20];
					snprintf(smatch, 20, " MATCH : %d ", match);
					count_match.RenderText(smatch, font, g_screen, 1);
				}
				if (pk == 1)
				{
					char smatch[20];
					snprintf(smatch, 20, " %d  ", match);
					count_match.RenderText(smatch, font, g_screen, 1);

					char smatch2[20];
					snprintf(smatch2, 20, " :  %d  ", match_pk);
					count_player.RenderText(smatch2, font, g_screen, 1);
				}
			}
		}

		x_ = 0, y_ = 0;
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

   begin.free();
p_player.Free();
p_bullet.Free();
p_player2.Free();
p_unti.Free();
count_match.free();
ready.free();
vs_bot.free();
 vs_1.free();
 tutorial_player1.free();
 tutorial_player2.free();
for (int i = 0; i < 2; i++)
{
	endgame[i].free();
	choose[i].free();
}
	close();
	return 0;
}