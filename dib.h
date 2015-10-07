#pragma once
#include <hge.h>
#include <hgesprite.h>
#include <hgeanim.h>
#include <hgerect.h>

const int cellSize = 40;

enum objtype { tcell, tborder, truby, tgold, thelmet, tgreensun, tseashell, tsunpart };
enum actions { do_shine, do_spin };

class Dib
{
protected:
	float Xpos, Ypos;// координаты
	long num;// номер
public:
	int GetNum() { return num; } // возвращает номер
	void SetNum(int n) { num = n; }
	float GetXpos() { return Xpos; } // возвращает позицию по Х
	float GetYpos() { return Ypos; } // возвращает позицию по Y
	void SetXpos(float x) { Xpos = x; }//устанавливает позицию по X
	void SetYpos(float y) { Ypos = y; }//устанавливает позицию по Y
	virtual void Render() { }; // перерисовка

	virtual ~Dib() = 0 { };// чисто виртуальный деструктор
};