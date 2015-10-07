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
	Ruby *pRuby1, *pRuby2;//указатели 
	hgeFont *gFont;//глобальный объект - шрифт
	Font *score;//объект-шрифт дл€ вывода очков

	//текстуры
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
	vector <SunPart*> sunvec;// части солнца
	vector <Cell*> lockvec;//vector contains locks
	vector <Font*> scorelabs;//vector contains score labels
	vector <Font*> xrowlabs;//vector contains labels for counts of deleted rows

	long number;// main object number!!!

	bool start_moving;//началось движение фишек
	bool start_game;//флажок начала игры
public:
	Level() { };
	Level(HGE *hge, float x, float y);
	~Level();

	int Render(float Xcur, float Ycur, float thisTime);//перерисовка
	void Load_Level(const char *fn);//загрузить уровень из внешнего файла
//	void CheckMouseMove(float Xcur, float Ycur, float thisTime);//проверить перемещение мыши
	void CheckMouseDown(float Xcur, float Ycur, float thisTime);//проверить координаты мыши при нажатии клавиши
	void Moving();//функци€ перемещени€
	void MakeBorders(const int num);//построить границы
	bool Get_StartGame() { return start_game; }//возвращает началась ли игра
	bool Get_StartMoving() { return start_moving; }//возвращает началось ли перемещение фишек (имеено перемещение, а не падение(!!!))
	bool CheckCompositions(Ruby *ruby);//проверить не составл€ют ли фишки комбинацию
	void CheckToDelete();//проверить состо€ни€ фишек, может можно что-то удалить
	void ToNull();//обнулить указатели
	void Falling();//функци€ падени€ фишек
	void GoDown(Ruby *t);//опустить фишки
	void Create_Dib(float xpos);//создать фишку
	void DoIt(Ruby *t);//осуществить действи€
	void CheckLocks();//проверить замки
	void CheckMouseMoveOverload(float Xcur, float Ycur, float thisTime);//проверить координаты мыши при перемещении
	void Check_Remove(SunPart *sun);//провер€ет, дошла ли частица солнца до низу
	void FormSun(SunPart *sun);//формирует солнце
	void Create_Labs(int i, float x, float y);//создаЄт надписи
};