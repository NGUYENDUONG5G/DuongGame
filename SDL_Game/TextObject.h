#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include"CommonFunc.h"

class TextObject
{
public:
	TextObject();
	~TextObject();

	enum TextColor
	{
		RED_TEXT = 0,
	WHITE_TEXT=1,
	BLACK_TEXT=2,

	};

	
	

	SDL_Color SetColor(int type);

	void RenderText(const char* data_, TTF_Font* gFont,SDL_Renderer* screen,int k);
	
	void set_xy(const int& x_, const int& y_)
	{
		gTextRect.x = x_;
		gTextRect.y = y_;

	}
	
	void free();

	SDL_Rect get_Rect() { return gTextRect; }
private:
	std::string str_val_;
	
	SDL_Texture* texture_;

	SDL_Rect gTextRect = {0,0,0,0 };
	
};


#endif // !TEXT_OBJECT_H_

