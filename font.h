#pragma once 
#include <hgefont.h>
#include "dib.h"

enum mode { space, mplus, xrow };//3 режима перерисовки: с пустым местом, с плюсом, с иксом

class Font : public Dib
{
private:
		hgeFont *font;//объект - шрифт
		int score, tarscore;//очки
		float mult;//множитель для изменения размера
		float TimeToBorn;//время рождения
		bool visible;//видимость
public:
		Font();
		Font(hgeFont *f, float time, int sc, float xpos, float ypos, float mul);
		Font(const Font& ffont);
		~Font();

		void Render(int mode, float thisTime);//всего 3 режима
		void Add(int num);
};