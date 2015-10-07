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

	//интерпол€ци€ по сплайну
	SplinePath spx, spy;
	//система частиц дл€ шлейфа
	hgeParticleSystem *partsys;

	short name;//цифровое им€
	bool  onPlace,//на месте в мозаике
		  doFire;//делать огонь	
public: 
	SunPart();
	SunPart(short Name, HGE *hge, const char* pathTex, int typ, int inum, float x, float y);
	SunPart(const SunPart& sunpart);
	SunPart& operator=(const SunPart& sunpart);//перегруженный оператор присваивани€
	~SunPart();

	bool Render(float x, float y);	
	bool CheckMousePos(float Xcur, float Ycur);
	bool Move();
	void Shine_Play() {};//достались по наследству :)
	void Spin_Play() {};//необходимо переопределить
	void Spin_Stop() {};//ничего делать им не надо
						//оставлены дл€ совместимости
	short GetName() { return name; }//возвращает им€
	void addXKey(float value) { spx.addKey(value); }//добавит значение в список интерполировани€
	void addYKey(float value) { spy.addKey(value); }//добавит значение в список интерполировани€
	void ComputeX() { spx.CalculateGradient(); }//интерполировать сплайном
	void ComputeY() { spy.CalculateGradient(); }//интерполировать сплайном
	bool GetOnPlace() { return onPlace; }//находитс€ ли кусочек в мозаике
};						
