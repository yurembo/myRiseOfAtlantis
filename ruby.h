#pragma once
#include "dib.h"
#include "cell.h"

class Ruby : public Dib
{
private:
	hgeAnimation *shine_anim, *spin_anim;// animations
	int activity;//executed activity
	bool lock;//������
	Cell *linklock;//��������� �� ��������� ������
protected:
	int type,//type
		fall_times;//���-�� �������
	float tarX, tarY,// target X and Y
		  time;//����� 
	bool hrem,// ���� �������� �����, ������������ �������������� ����������
	     vrem,// ���� �������� �����, ������������ ������������ ����������
		 go_back,//���� "��� �����"
		 fall,//�������
		 removed;// ������
public:
	Ruby();// default constructor
	Ruby(HTEXTURE *tex, int typ, int n, float x, float y);
	Ruby(HGE *hge, const char* pathTex, int typ, int inum, float x, float y);
	Ruby(const Ruby& ruby);//����������� �����������
	Ruby& operator=(const Ruby& ruby);//������������� �������� ������������
	~Ruby();

	virtual bool Render(float x, float y);//������������, �.�. ���������� ��������, � ������� ��� ������ �� ����
	int GetType() { return type; } // ���������� ��� �������
	virtual void Shine_Play();
	virtual void Spin_Play();
	virtual bool CheckMousePos(float Xcur, float Ycur);
	virtual void Spin_Stop();
	int GetActivity() { return activity; }
	virtual bool Move();
	void SettarX(float xpos) { tarX = xpos; }//����������� ������� �
	void SettarY(float ypos) { tarY = ypos; }//����������� ������� Y
	float GettarY() { return tarY; }//���������� ������� Y
	float GettarX() { return tarX; }//���������� ������� X
	void SetHRem(bool remove) { hrem = remove; }//������������� ���� ��������
	bool GetHRem() { return hrem; }//��������� ���� ��������
	void SetVRem(bool remove) { vrem = remove; }//������������� ���� ��������
	bool GetVRem() { return vrem; }//��������� ���� ��������
	void SetGoBack(bool go) { go_back = go; } ;//������������� ����
	bool GetGoBack() { return go_back; }//���������� ����
	void SetFall(bool f) { fall = f; }//������������� ���� �������
	bool GetFall() { return fall; }//���������� ���� �������
	void SetLock(bool l);//������������� ������� ����������
	bool GetLock() { return lock; }//���������� ������� ���������� 
	void SetLinkLock(Cell *llock) { linklock = llock; }//����������� ������-�����
	bool GetLinkLock() { if (linklock != NULL) return true; else return false; }//�������� �� �����
	void SetFallTimes(int times) { fall_times = times; }//���������� ���������� �������
	int GetFallTimes() { return fall_times; }//���������� ���������� �������
	bool GetRemoved() { return removed; }//���������� ��������� ��������
	void SetRemoved(bool rem) { removed = rem; }//���������� ��������� ��������
};