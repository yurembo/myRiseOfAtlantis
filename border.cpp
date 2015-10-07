#include "border.h"

Border::Border()//default constructor
{
	num = 0;
	Xpos = 0;
	Ypos = 0;
	rot = 0;

	spr = NULL;
}

Border::Border(HTEXTURE *tex, int n, float xtex, float ytex, float xpos, float ypos, float rotate)
{
	num = n;
	Xpos = xpos;
	Ypos = ypos;
	rot = rotate;
	
	spr = new hgeSprite(*tex, xtex, ytex, float(cellSize), float(cellSize));
}

Border::Border(const Border& border)
{
	num = border.num;
	Xpos = border.Xpos;
	Ypos = border.Ypos;
	rot = border.rot;

	spr = border.spr;
}

Border::~Border()
{
	num = 0;
	Xpos = 0;
	Ypos = 0;
	rot = 0;

	delete spr;
	spr = NULL;
}

void Border::Render(float x, float y)
{
	spr->RenderEx(x + Xpos, y + Ypos, rot, 1.0, 0.0);
}