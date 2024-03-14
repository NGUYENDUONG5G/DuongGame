#include "stdafx.h"
#include "CommonFunc.h"
 #include "BaseObject.h"
#include"game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include  "ThreatsObject.h"



#undef main
BaseObject g_background;



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
	}
	return success;

}


bool LoadBackground() {
	bool ret = g_background.LoadImg("img//newbkgr4.jpg", g_screen);
	if (ret == false) return false;
	return true;
}
void close() {
	g_background.Free();


	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}
// T?o m?y con bot



int main(int arc, char* argv[]) 
{

	ImpTimer fps_timer;
	float vtrix;
	float vtriy;
	int xem_xet;

	float vitribotx;
	float vitriboty;

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
	p_threat.LoadImg("img//threat_left.png",g_screen);
	p_threat.set_clips();



	bool is_quit = false;
	while (!is_quit)
	{
		fps_timer.start();

		while (SDL_PollEvent(&g_event) != 0) {


			if (g_event.type == SDL_QUIT) {

				is_quit = true;

			}
			p_player.HandelInputAction(g_event, g_screen);
		}


		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);




		Map map_data = game_map.getMap();


		vtrix = p_player.vitri_x();
		vtriy = p_player.vitri_y();
		

		vitribotx = p_threat.get_x_pos();
		vitriboty = p_threat.get_y_pos();
		p_player.Swap(vitribotx,vitriboty );
		p_player.HandleBullet(g_screen);

		p_player.SetMapXY(map_data.start_x_, map_data.start_y_);

		p_player.Doplayer(map_data);

		p_player.Show(g_screen);

		game_map.SetMap(map_data);

		game_map.DrawMap(g_screen);



		p_threat.SetMapXY(map_data.start_x_, map_data.start_y_);
		p_threat.ktraN(vtrix, vtriy);
		
		p_threat.ImpMoveType(g_screen);
		p_threat.DoPlayer(map_data);
		p_threat.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
		p_threat.Show(g_screen);

		xem_xet = 0;



		// tạo va chạm của người và bot
		std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();

		for (int r = 0; r < bullet_arr.size(); r++)
		{
			BulletObject* p_bullet = bullet_arr.at(r);
			if (p_bullet != NULL)
			{


				SDL_Rect tRect;
				tRect.x = p_threat.GetRect().x;
				tRect.y = p_threat.GetRect().y;
				tRect.w = p_threat.get_width_frame();
				tRect.h = p_threat.get_height_frame();

				SDL_Rect bRect = p_bullet->GetRect();




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



	close();
	return 0;
}