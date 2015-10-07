#pragma once 
#include <hgefont.h>
#include "dib.h"

enum mode { space, mplus, xrow };//3 ������ �����������: � ������ ������, � ������, � �����

class Font : public Dib
{
private:
		hgeFont *font;//������ - �����
		int score, tarscore;//����
		float mult;//��������� ��� ��������� �������
		float TimeToBorn;//����� ��������
		bool visible;//���������
public:
		Font();
		Font(hgeFont *f, float time, int sc, float xpos, float ypos, float mul);
		Font(const Font& ffont);
		~Font();

		void Render(int mode, float thisTime);//����� 3 ������
		void Add(int num);
};