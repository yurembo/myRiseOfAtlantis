#include <vector>
#include <hgeparticle.h>
#include "Spline\Spline.h"
#include "ruby.h"

const int sunSize = 64;

class SunPart : public Ruby
{
private:
	HGE* Hge;
	HTEXTURE suntex;
	HTEXTURE partsystex;
	hgeSprite *spr;
	hgeSprite *partsysspr;

	//������������ �� �������
	SplinePath spx, spy;
	//������� ������ ��� ������
	hgeParticleSystem *partsys;

	short name;//�������� ���
	bool  onPlace,//�� ����� � �������
		  doFire;//������ �����	
public: 
	SunPart();
	SunPart(short Name, HGE *hge, const char* pathTex, int typ, int inum, float x, float y);
	SunPart(const SunPart& sunpart);
	SunPart& operator=(const SunPart& sunpart);//������������� �������� ������������
	~SunPart();

	bool Render(float x, float y);	
	bool CheckMousePos(float Xcur, float Ycur);
	bool Move();
	void Shine_Play() {};//��������� �� ���������� :)
	void Spin_Play() {};//���������� ��������������
	void Spin_Stop() {};//������ ������ �� �� ����
						//��������� ��� �������������
	short GetName() { return name; }//���������� ���
	void addXKey(float value) { spx.addKey(value); }//������� �������� � ������ ����������������
	void addYKey(float value) { spy.addKey(value); }//������� �������� � ������ ����������������
	void ComputeX() { spx.CalculateGradient(); }//��������������� ��������
	void ComputeY() { spy.CalculateGradient(); }//��������������� ��������
	bool GetOnPlace() { return onPlace; }//��������� �� ������� � �������
};						
