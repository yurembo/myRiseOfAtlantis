#pragma once
#include "dib.h"

class Cell : public Dib
{
protected:
	hgeSprite *spr;
public:
	Cell();//default constructor
	Cell(HTEXTURE *tex, int n, float x, float y);//constructor with parameters
	Cell(HTEXTURE *tex, int n, float x, float y, bool lock);//constructor with parameters
	Cell(const Cell& cell);//copy constructor
	~Cell();//destructor

	virtual void Render(float x, float y);
};