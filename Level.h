#include <vector>
#include "tinyxml\tinyxml.h"
#include "cell.h"
#include "ruby.h"
#include "sunpart.h"
#include "border.h"
#include "font.h"

using namespace std;

class Level : public Dib
{
private:
	HGE *Hge;
	hgeSprite *bgSpr;// backgroud sprite
	Ruby *pRuby1, *pRuby2;//��������� 
	hgeFont *gFont;//���������� ������ - �����
	Font *score;//������-����� ��� ������ �����

	//��������
	HTEXTURE bgTex, 
	         cellTex, 
			 rubyTex, 
			 goldTex, 
			 helmetTex,
	         greensunTex, 
			 seashellTex,
	   		 borderTex,
			 lockTex;

	vector <Cell*> cellvec;// vector contains Cell objects
	vector <Ruby*> rubyvec;// vector contains Ruby objects	
	vector <Border*> bordervec;// vector contains Border objects
	vector <SunPart*> sunvec;// ����� ������
	vector <Cell*> lockvec;//vector contains locks
	vector <Font*> scorelabs;//vector contains score labels
	vector <Font*> xrowlabs;//vector contains labels for counts of deleted rows

	long number;// main object number!!!

	bool start_moving;//�������� �������� �����
	bool start_game;//������ ������ ����
public:
	Level() { };
	Level(HGE *hge, float x, float y);
	~Level();

	int Render(float Xcur, float Ycur, float thisTime);//�����������
	void Load_Level(const char *fn);//��������� ������� �� �������� �����
//	void CheckMouseMove(float Xcur, float Ycur, float thisTime);//��������� ����������� ����
	void CheckMouseDown(float Xcur, float Ycur, float thisTime);//��������� ���������� ���� ��� ������� �������
	void Moving();//������� �����������
	void MakeBorders(const int num);//��������� �������
	bool Get_StartGame() { return start_game; }//���������� �������� �� ����
	bool Get_StartMoving() { return start_moving; }//���������� �������� �� ����������� ����� (������ �����������, � �� �������(!!!))
	bool CheckCompositions(Ruby *ruby);//��������� �� ���������� �� ����� ����������
	void CheckToDelete();//��������� ��������� �����, ����� ����� ���-�� �������
	void ToNull();//�������� ���������
	void Falling();//������� ������� �����
	void GoDown(Ruby *t);//�������� �����
	void Create_Dib(float xpos);//������� �����
	void DoIt(Ruby *t);//����������� ��������
	void CheckLocks();//��������� �����
	void CheckMouseMoveOverload(float Xcur, float Ycur, float thisTime);//��������� ���������� ���� ��� �����������
	void Check_Remove(SunPart *sun);//���������, ����� �� ������� ������ �� ����
	void FormSun(SunPart *sun);//��������� ������
	void Create_Labs(int i, float x, float y);//������ �������
};