#include"stdafx.h"
#include "TextObject.h"

TextObject::TextObject()
{
	
	texture_ = NULL;


}

TextObject::~TextObject()
{


}



SDL_Color TextObject::SetColor(int type)
{
	SDL_Color color;
	if (type == RED_TEXT)
	{
	 color = { 255,0,0 ,255};
		

	}
	else if (type == WHITE_TEXT)
	{
		 color = { 255,255,255 ,255};
	
	}
	else if (type == BLACK_TEXT)
	{
		 color = { 0,0,0,255 };


	}
	return color;
}

void TextObject::RenderText(const char* data_, TTF_Font* gFont,SDL_Renderer* screen ,int k)
{
	free();
	
	SDL_Color color = SetColor(k);
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, data_, color);
	if (textSurface != NULL)
	{
		texture_ = SDL_CreateTextureFromSurface(screen, textSurface);
		if (texture_ != NULL)
		{
			gTextRect.w = textSurface->w;
			gTextRect.h = textSurface->h;
			SDL_RenderCopy(screen, texture_,NULL, &gTextRect );
		}
		
		SDL_FreeSurface(textSurface);
		
	}

	
	
}
void TextObject::free()
{

	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		gTextRect.w = 0;
		gTextRect.h = 0;
	}
}