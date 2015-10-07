#include "cell.h"

Cell::Cell()//default constructor
{
	num = 0;
	Xpos = 0;
	Ypos = 0;

	spr = NULL;
}
//конструктор дл€ €чеек пола
Cell::Cell(HTEXTURE *tex, int n, float x, float y)
{
	num = n;
	Xpos = x;
	Ypos = y;
	
	spr = new hgeSprite(*tex, x, y, float(cellSize), float(cellSize));
}
//конструктор дл€ замка
Cell::Cell(HTEXTURE *tex, int n, float x, float y, bool lock)
{
	num = n;
	Xpos = x;
	Ypos = y;
	
	spr = new hgeSprite(*tex, x, y, float(cellSize), float(cellSize));
	spr->SetTextureRect(0, 0, 46, 46);
}

Cell::Cell(const Cell& cell)
{
	num = cell.num;
	Xpos = cell.Xpos;
	Ypos = cell.Ypos;

	spr = cell.spr;
}

Cell::~Cell()
{
	num = 0;
	Xpos = 0;
	Ypos = 0;

	spr = NULL;
	delete spr;
}

void Cell::Render(float x, float y)
{
	spr->Render(x + Xpos, y + Ypos);
}