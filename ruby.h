#pragma once
#include "dib.h"
#include "cell.h"

class Ruby : public Dib
{
private:
	hgeAnimation *shine_anim, *spin_anim;// animations
	int activity;//executed activity
	bool lock;//заперт
	Cell *linklock;//указатель на связанный объект
protected:
	int type,//type
		fall_times;//кол-во падений
	float tarX, tarY,// target X and Y
		  time;//время 
	bool hrem,// флаг удаления фишек, составляющих горизонтальную композицию
	     vrem,// флаг удаления фишек, составляющих вертикальную композицию
		 go_back,//флаг "иди назад"
		 fall,//падение
		 removed;// удален
public:
	Ruby();// default constructor
	Ruby(HTEXTURE *tex, int typ, int n, float x, float y);
	Ruby(HGE *hge, const char* pathTex, int typ, int inum, float x, float y);
	Ruby(const Ruby& ruby);//конструктор копирования
	Ruby& operator=(const Ruby& ruby);//перегруженный оператор присваивания
	~Ruby();

	virtual bool Render(float x, float y);//невиртуальна, т.к. возвращает значение, а потомку это делать не надо
	int GetType() { return type; } // возвращает тип объекта
	virtual void Shine_Play();
	virtual void Spin_Play();
	virtual bool CheckMousePos(float Xcur, float Ycur);
	virtual void Spin_Stop();
	int GetActivity() { return activity; }
	virtual bool Move();
	void SettarX(float xpos) { tarX = xpos; }//присваевает целевой Х
	void SettarY(float ypos) { tarY = ypos; }//присваевает целевой Y
	float GettarY() { return tarY; }//возвращает целевой Y
	float GettarX() { return tarX; }//возвращает целевой X
	void SetHRem(bool remove) { hrem = remove; }//устанавливаем флаг удаления
	bool GetHRem() { return hrem; }//проверяем флаг удаления
	void SetVRem(bool remove) { vrem = remove; }//устанавливаем флаг удаления
	bool GetVRem() { return vrem; }//проверяем флаг удаления
	void SetGoBack(bool go) { go_back = go; } ;//устанавливаем флаг
	bool GetGoBack() { return go_back; }//возвращаем флаг
	void SetFall(bool f) { fall = f; }//устанавливаем флаг падения
	bool GetFall() { return fall; }//возвращаем флаг падения
	void SetLock(bool l);//устанавливает признак закрытости
	bool GetLock() { return lock; }//возвращает признак закрытости 
	void SetLinkLock(Cell *llock) { linklock = llock; }//привязывает объект-замок
	bool GetLinkLock() { if (linklock != NULL) return true; else return false; }//привязан ли замок
	void SetFallTimes(int times) { fall_times = times; }//установить количество падений
	int GetFallTimes() { return fall_times; }//возвратить количество падений
	bool GetRemoved() { return removed; }//возвращает состояние удаления
	void SetRemoved(bool rem) { removed = rem; }//установить состояние удаления
};