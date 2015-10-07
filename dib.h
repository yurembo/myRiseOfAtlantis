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
	float Xpos, Ypos;// ����������
	long num;// �����
public:
	int GetNum() { return num; } // ���������� �����
	void SetNum(int n) { num = n; }
	float GetXpos() { return Xpos; } // ���������� ������� �� �
	float GetYpos() { return Ypos; } // ���������� ������� �� Y
	void SetXpos(float x) { Xpos = x; }//������������� ������� �� X
	void SetYpos(float y) { Ypos = y; }//������������� ������� �� Y
	virtual void Render() { }; // �����������

	virtual ~Dib() = 0 { };// ����� ����������� ����������
};