#include "Level.h"

Level::Level(HGE *hge, float x, float y)
{
	num = 0;
	Xpos = x;
	Ypos = y;
	Hge = hge;	

	bgTex = NULL;
	cellTex = NULL;
	rubyTex = NULL;
	goldTex = NULL; 
	helmetTex = NULL;
	greensunTex = NULL;
	seashellTex = NULL;
	borderTex = NULL;
	lockTex = NULL;

	pRuby1 = NULL;
	pRuby2 = NULL;
	number = 0;
	start_game = false;
	start_moving = false;
	Hge->Random_Seed();

	gFont = new hgeFont("Data//Font//Score.fnt");
	score = new Font(gFont, 0, 0, 225, 340, 1.4f);

	Load_Level("Data\\Levels\\level2.xml");

	start_game = true;
}

Level::~Level()
{
	Xpos = 0;
	Ypos = 0;
	number = 0;
	start_moving = 0;
	start_game = false;

	if (sunvec.size() > 0) {
		for (int i = 0; i < sunvec.size(); ++i) {
			if (sunvec[i] != NULL) {
				delete sunvec[i];
			}
		}
		sunvec.clear();
	}

	if (rubyvec.size() > 0) {
		for (int i = 0; i < rubyvec.size(); ++i) {
			if (rubyvec[i] != NULL) {
				delete rubyvec[i];
			}
		}
		rubyvec.clear();
	}

	if (cellvec.size() > 0) {
		for (int i = 0; i < cellvec.size(); ++i) {
			if (cellvec[i] != NULL) {
				delete cellvec[i];
			}
		}
		cellvec.clear();
	}

	if (bordervec.size() > 0) {
		for (int i = 0; i < bordervec.size(); ++i) {
			if (bordervec[i] != NULL) {
				delete bordervec[i];
			}
		}
		bordervec.clear();
	}

	if (lockvec.size() > 0) {
		for (int i = 0; i < lockvec.size(); ++i) {
			if (lockvec[i] != NULL) {
				delete lockvec[i];
			}
		}
		lockvec.clear();
	}

	if (bgSpr != NULL) delete bgSpr;

	if (bgTex != NULL) Hge->Texture_Free(bgTex);
	if (cellTex != NULL) Hge->Texture_Free(cellTex);
	if (rubyTex != NULL) Hge->Texture_Free(rubyTex);
	if (goldTex != NULL) Hge->Texture_Free(goldTex);
	if (helmetTex != NULL) Hge->Texture_Free(helmetTex);
	if (greensunTex != NULL) Hge->Texture_Free(greensunTex);
	if (seashellTex != NULL) Hge->Texture_Free(seashellTex);
	if (borderTex != NULL) Hge->Texture_Free(borderTex);
	if (lockTex != NULL) Hge->Texture_Free(lockTex);

	bgTex = NULL;
	cellTex = NULL;
	rubyTex = NULL;
	goldTex = NULL; 
	helmetTex = NULL;
	greensunTex = NULL;
	seashellTex = NULL;
	borderTex = NULL;
	lockTex = NULL;

		if (scorelabs.size() > 0) {
			for (int i = 0; i < scorelabs.size(); ++i) {
				delete scorelabs[i];
			}
			scorelabs.clear();
		}

		if (xrowlabs.size() > 0) {
			for (int i = 0; i < xrowlabs.size(); ++i) {
				delete xrowlabs[i];
			}
			xrowlabs.clear();
		}
	
		if (score != NULL) {
			delete score;
			score = NULL;
		}

		if (gFont != NULL) {
			delete gFont;
			gFont = NULL;
		}

}

void Level::Load_Level(const char *fn)
{
	 // код парсинга xml файла 
	const char *pfile = "file", *pobject = "object", *pcell = "cell", 
	           *pruby = "ruby", *pgold = "gold", *phelmet = "helmet",
			   *pgreensun = "green sun", *pseashell = "seashell",
			   *pbackground = "background", *plock = "lock", 
			   *psunp = "sun p";
	const char *elementName, *ttype, *path = NULL, *xp, *yp;
	float xpos, ypos;

	/*int*/ number = 1;// object number
	Cell *cell;//объект - ячейка для пола
	Ruby *ruby;//объект - фишка
	SunPart *sunpart;//объект - часть солнца

	TiXmlDocument doc(fn);
	doc.LoadFile();
	TiXmlElement* root = doc.FirstChildElement("level");
	TiXmlElement* element = root->FirstChildElement();

	while (element != NULL)
{
	elementName = element->Value();
	if (_stricmp(elementName, pfile) == 0)//file
	{
		TiXmlAttribute* fattr = element->FirstAttribute();//first attribute
		if (fattr)
		{
			ttype = fattr->Value();
			TiXmlAttribute* sattr = fattr->Next();//second attribute
			path = sattr->Value();
			///////////// LOAD ///////////////
			if (_stricmp(ttype, pbackground) == 0)
			bgTex = Hge->Texture_Load(path); else
			if (_stricmp(ttype, pcell) == 0)
			cellTex = Hge->Texture_Load(path); else
			if (_stricmp(ttype, pruby) == 0)
			rubyTex = Hge->Texture_Load(path); else
			if (_stricmp(ttype, pgold) == 0)
			goldTex = Hge->Texture_Load(path); else
			if (_stricmp(ttype, phelmet) == 0)
			helmetTex = Hge->Texture_Load(path); else
			if (_stricmp(ttype, pgreensun) == 0)
			greensunTex = Hge->Texture_Load(path); else
			if (_stricmp(ttype, pseashell) == 0)
			seashellTex = Hge->Texture_Load(path); else
			if (_stricmp(ttype, plock) == 0)
			lockTex = Hge->Texture_Load(path);
			///////////////////////////////////
			xp = NULL;
			yp = NULL;
		element = element->NextSiblingElement();
		}
	} else
	if (_stricmp(elementName, pobject) == 0)//object
	{
		TiXmlAttribute* fattr = element->FirstAttribute();//first attribute
		if (fattr)
		{
			ttype = fattr->Value();
			TiXmlAttribute* sattr = fattr->Next();//second attribute
			xp = sattr->Value();
			TiXmlAttribute* tattr = sattr->Next();//third attribute
			yp = tattr->Value();
			if (xp != NULL)
			{
				xpos = atof(xp);
			}
			if (yp != NULL)
			{
				ypos = atof(yp);
			}
			// вызываю конструктор объекта
			if ((_stricmp(ttype, pbackground) == 0) && (bgTex != NULL))
			{
			bgSpr = new hgeSprite(bgTex, 0, 0, 800, 600);
			} else
			if ((_stricmp(ttype, pcell) == 0) && (cellTex != NULL))
			{
			cell = new Cell(&cellTex, number, xpos, ypos);
			cellvec.push_back(cell);
			} else
			if ((_stricmp(ttype, pruby) == 0) && (rubyTex != NULL))
			{
			ruby = new Ruby(&rubyTex, truby, number, xpos, ypos);
			rubyvec.push_back(ruby);
			} else
			if ((_stricmp(ttype, pgold) == 0) && (goldTex != NULL))
			{
			ruby = new Ruby(&goldTex, tgold, number, xpos, ypos);
			rubyvec.push_back(ruby);
			} else
			if ((_stricmp(ttype, phelmet) == 0) && (helmetTex != NULL))
			{
			ruby = new Ruby(&helmetTex, thelmet, number, xpos, ypos);
			rubyvec.push_back(ruby);
			} else
			if ((_stricmp(ttype, pgreensun) == 0) && (greensunTex != NULL))
			{
			ruby = new Ruby(&greensunTex, tgreensun, number, xpos, ypos);
			rubyvec.push_back(ruby);
			} else
			if ((_stricmp(ttype, pseashell) == 0) && (seashellTex != NULL))
			{
			ruby = new Ruby(&seashellTex, tseashell, number, xpos, ypos);
			rubyvec.push_back(ruby);
			} else
			if ((strstr(ttype, psunp) != NULL) && (path != NULL))
			{
			const char *cnum = strpbrk(ttype, "1234");
			short num = atoi(cnum);
			sunpart = new SunPart(num, Hge, path, tsunpart, number, xpos, ypos); 
			sunvec.push_back(sunpart);
			} else 
			if ((_stricmp(ttype, plock) == 0) && (lockTex != NULL))
			{
			cell = new Cell(&lockTex, number, xpos, ypos, true);
			lockvec.push_back(cell);
			}
			number++;
		element = element->NextSiblingElement();
		}
	}
}
if (!cellvec.empty()) MakeBorders(number);
if (!lockvec.empty()) CheckLocks();
}

void Level::CheckLocks()//функция, повидимому, будет выполнятся очень долго,
{						//но ничего страшного, поскольку она будет вызываться 
vector <Cell*>::iterator iter = lockvec.begin();//лишь однажды - во время загрузки,
while (iter != lockvec.end())//и не важно как долго будет загружаться игра 
{//(беря в расчет разумные пределы, конечно), важно, чтобы она исполнялась,
vector <Ruby*>::iterator ter = rubyvec.begin();//как гиперпропеллер с турбоподдувом :)
while (ter != rubyvec.end())
{
if (((*ter)->GetXpos() == (*iter)->GetXpos()) && ((*ter)->GetYpos() == (*iter)->GetYpos()))
{
(*ter)->SetLock(true);
Cell *cell = new Cell(&lockTex, lockvec.size() + 1, (*ter)->GetXpos(), (*ter)->GetYpos(), true);
(*ter)->SetLinkLock(cell);
}//if
ter++;
}//while
iter++;
}//while
}

void Level::MakeBorders(const int num)
{
int number = num;
borderTex = Hge->Texture_Load("Data//Scope.png");
//cell
	vector <Cell*>::iterator iter = cellvec.begin();
	while (iter != cellvec.end())
	{
	Border *border;
		bool top = true;
		bool bottom = true;
		bool left = true;
		bool right = true;
		bool upleft = true;
		bool upright = true;
		bool bottomleft = true;
		bool bottomright = true;

	vector <Cell*>::iterator ter = cellvec.begin();
	while (ter != cellvec.end())
	{
		if ((((*iter)->GetYpos() - cellSize == (*ter)->GetYpos()) && ((*iter)->GetXpos() == (*ter)->GetXpos()))
		   || (((*iter)->GetXpos() - cellSize == (*ter)->GetXpos()) && ((*iter)->GetYpos() == (*ter)->GetYpos())))
		{
		upleft = false;
		}
		if ((((*iter)->GetYpos() - cellSize == (*ter)->GetYpos()) && ((*iter)->GetXpos() == (*ter)->GetXpos()))
		   || (((*iter)->GetXpos() + cellSize == (*ter)->GetXpos()) && ((*iter)->GetYpos() == (*ter)->GetYpos())))
		{
		upright = false;
		}
		if ((((*iter)->GetYpos() + cellSize == (*ter)->GetYpos()) && ((*iter)->GetXpos() == (*ter)->GetXpos()))
		   || (((*iter)->GetXpos() - cellSize == (*ter)->GetXpos()) && ((*iter)->GetYpos() == (*ter)->GetYpos())))
		{
		bottomleft = false;
		}
		if ((((*iter)->GetYpos() + cellSize == (*ter)->GetYpos()) && ((*iter)->GetXpos() == (*ter)->GetXpos()))
		   || (((*iter)->GetXpos() + cellSize == (*ter)->GetXpos()) && ((*iter)->GetYpos() == (*ter)->GetYpos())))
		{
		bottomright = false;
		}
		if (((*iter)->GetYpos() - cellSize == (*ter)->GetYpos()) && ((*iter)->GetXpos() == (*ter)->GetXpos())) 
		{
		top = false;
		} 
	 	if (((*iter)->GetYpos() + cellSize == (*ter)->GetYpos()) && ((*iter)->GetXpos() == (*ter)->GetXpos())) 
		{
		bottom = false;
		} 
		if (((*iter)->GetXpos() - cellSize == (*ter)->GetXpos()) && ((*iter)->GetYpos() == (*ter)->GetYpos())) 
		{
		left = false;
		} 
		if (((*iter)->GetXpos() + cellSize == (*ter)->GetXpos()) && ((*iter)->GetYpos() == (*ter)->GetYpos())) 
		{
		right = false;
		}  
		ter++;
	}
	if (top)
	{
	border = new Border(&borderTex, number, 0, 0, (*iter)->GetXpos(), (*iter)->GetYpos() - (cellSize / 2 + 5), 0.0);
	bordervec.push_back(border);
	number++;
	}
	if (bottom)
	{
	border = new Border(&borderTex, number, 0, 0, (*iter)->GetXpos(), (*iter)->GetYpos() + cellSize / 2, 0.0);
	bordervec.push_back(border);
	number++;
	}
	if (left)
	{
	border = new Border(&borderTex, number, 0, 0, (*iter)->GetXpos() + cellSize / 2, (*iter)->GetYpos(), 1.57f);
	bordervec.push_back(border);
	number++;
	}
	if (right)
	{
	border = new Border(&borderTex, number, 0, 0, (*iter)->GetXpos() + cellSize + cellSize / 2 + 5, (*iter)->GetYpos(), 1.57f);
	bordervec.push_back(border);
	number++;
	}
	if (upleft)
	{
	border = new Border(&borderTex, number, 0, 81, (*iter)->GetXpos() + cellSize / 2, (*iter)->GetYpos() + cellSize / 2, 3.15f);
	bordervec.push_back(border);
	number++;
	}
	if (upright)
	{
	border = new Border(&borderTex, number, 0, 81, (*iter)->GetXpos() + cellSize / 2, (*iter)->GetYpos() + cellSize / 2, -1.5f);
	bordervec.push_back(border);
	number++;
	}
	if (bottomleft)
	{
	border = new Border(&borderTex, number, 0, 81, (*iter)->GetXpos() + cellSize / 2, (*iter)->GetYpos() + cellSize / 2, 1.55f);
	bordervec.push_back(border);
	number++;
	}
	if (bottomright)
	{
	border = new Border(&borderTex, number, 0, 81, (*iter)->GetXpos() + cellSize / 2, (*iter)->GetYpos() + cellSize / 2, 0);
	bordervec.push_back(border);
	number++;
	}
	iter++;
	}
}

int Level::Render(float Xcur, float Ycur, float thisTime)
{
int back = 1;
int win = 0;//накапливает количество кусочков в мозике
//background
    if (bgSpr != NULL) bgSpr->Render(0, 0);
//cell
	vector <Cell*>::iterator iter = cellvec.begin();
	while (iter != cellvec.end())
	{
	(*iter)->Render(Xpos, Ypos);
	iter++;
	}
//border
	vector <Border*>::iterator it = bordervec.begin();
	while (it != bordervec.end())
	{
	(*it)->Render(Xpos, Ypos);
	it++;
	}
//ruby
	vector <Ruby*> rv;// = rubyvec;//LOOK OUT!!!
	vector <Ruby*>::iterator ter = rubyvec.begin();
	while (ter != rubyvec.end())//Look Out!!!
	{
		if ((back == 1) && (((*ter)->GetFall())) || ((*ter)->GetRemoved())) back = 0;
		if ((*ter)->GetRemoved() || (*ter)->GetFall()) 
			rv.push_back(*ter);//LOOK OUT!!! second part
		if ((*ter)->Render(Xpos, Ypos)) 
			ter = rubyvec.erase(ter); else
		ter++;
	}
	//дополнительная переписовка, чтобы падающие фишки рисовались последними
	vector <Ruby*>::iterator r = rv.begin();
	while (r != rv.end())
	{
		if ((*r) != NULL) (*r)->Render(Xpos, Ypos);
		r++;
	}
//sun parts
	vector <SunPart*>::iterator suni = sunvec.begin();
	while (suni != sunvec.end())
	{
		(*suni)->Render(Xpos, Ypos);
		if ((back == 1) && ((*suni)->GetFall())) back = 0;
		if ((*suni)->GetOnPlace()) win++;
		suni++;
	}
	
//score labels
	vector <Font*>::iterator fontvec = scorelabs.begin();
	while (fontvec != scorelabs.end())
	{
		(*fontvec)->Render(mplus, thisTime);
		fontvec++;
	}
//labels show counts of deleted rows
	vector <Font*>::iterator xrowvec = xrowlabs.begin();
	while (xrowvec != xrowlabs.end())
	{
		(*xrowvec)->Render(xrow, thisTime);
		xrowvec++;
	}
	
if (win == sunvec.size()) back = 2;//в таком случае - ПОБЕДА!!!

//вывод очков
score->Render(space, thisTime);

if (start_moving) 
Moving(); 
else
Falling();

return back;
}
///////////////////////////////////////////////

void Level::Moving()//перемещает фишки: меняет их местами, типа, replace 
{
bool com1 = false, com2 = false;//you see, com = composition
static bool run1 = true, run2 = true;// yet runs
static bool back = false;//go back

if (pRuby2 != NULL)
	{
	pRuby2->Render(Xpos, Ypos);
	run2 = pRuby2->Move();
if (!run2) 
		{
		pRuby2->Spin_Stop();
		if (!back)
		com2 = CheckCompositions(pRuby2);
		else com2 = true;
		}
	}

if (pRuby1 != NULL) 
	{
	pRuby1->Render(Xpos, Ypos);
	run1 = pRuby1->Move();
if (!run1) 
		{
		pRuby1->Spin_Stop();
		if (!back) 
		com1 = CheckCompositions(pRuby1);
		else com1 = true;
		}
	}

if ((!run2) && (!run1))
{
if ((com2) || (com1)) 
{
back = false;
/////////////////////
SunPart *s1 = dynamic_cast<SunPart*>(pRuby1);//смотрим: объект какого класса
if (s1 != NULL)//если "часть солнца", тогда проводим необходимые действия
{
Check_Remove(s1);
s1 = NULL;
}
SunPart *s2 = dynamic_cast<SunPart*>(pRuby2);//смотрим: объект какого класса
if (s2 != NULL)//если "часть солнца", тогда проводим необходимые действия
{
Check_Remove(s2);
s2 = NULL;
}
/////////////////////
ToNull();
CheckToDelete();//Look Out!!!
}
if (((!com2) && (!com1)) && (!back))
{
if (pRuby1->GetType() != tsunpart)
pRuby1->Spin_Play();
//pRuby2->Spin_Play();
pRuby1->SettarX(pRuby2->GetXpos());
pRuby1->SettarY(pRuby2->GetYpos());
pRuby2->SettarX(pRuby1->GetXpos());
pRuby2->SettarY(pRuby1->GetYpos());
back = true;
}//if
}//if
//////////////
if ((pRuby1 == NULL) && (pRuby2 == NULL)) 
{
start_moving = false; 
}//if
}

void Level::Check_Remove(SunPart *sun)//проверяет, дошла ли частица солнца до низу
{
if ((sun != NULL) && (!sun->GetRemoved()))
{
	int down = 0;
	vector <Cell*>::iterator iter = cellvec.begin();
	while (iter != cellvec.end())
	{
		if (((*iter)->GetXpos() == sun->GetXpos()) && ((*iter)->GetYpos() > down))//ищем самую нижнюю половую ячейку в текущем столбце :)
			down = (*iter)->GetYpos();
	 iter++;
	}//while
	if (down == sun->GetYpos()) FormSun(sun);
}
}

void Level::ToNull()//обнуляет указатели
{
pRuby2->Spin_Stop();
pRuby2 = NULL;

pRuby1->Spin_Stop();
pRuby1 = NULL;
}
/////////////////////////////////////////////

void Level::Falling()//здесь происходит падение фишек
{
vector <Ruby*>::iterator ter = rubyvec.begin();
while (ter != rubyvec.end())
	{
		if ((*ter != NULL) && (*ter)->GetFall())
			{
			(*ter)->Render(Xpos, Ypos);//redraw
				if (!(*ter)->Move())
				{
					(*ter)->SetFall(false);
					if (CheckCompositions((*ter)))
						{
							CheckToDelete();
						}
				 } 
				
			}
	ter++;
	}

vector <SunPart*>::iterator tr = sunvec.begin();
while (tr != sunvec.end())
	{
		if ((*tr != NULL) && (*tr)->GetFall())
			{
				if (!(*tr)->Move())
				{
					(*tr)->SetFall(false);
						Check_Remove((*tr)); 
				}
			}
	tr++;
	}
}

void Level::FormSun(SunPart *sun)//формирует солнце
{
		sun->SetFall(true);
		sun->SetRemoved(true);
		GoDown(sun);
		Create_Dib(sun->GetXpos());
		sun->addXKey(sun->GetXpos());
		sun->addXKey(Hge->Random_Int(320, 400));
		sun->addXKey(Hge->Random_Int(70, 150));
		sun->addYKey(sun->GetYpos());
		sun->addYKey(Hge->Random_Int(180, 220));
		sun->addYKey(Hge->Random_Int(-30, 50));
short sh = sun->GetName();
	switch (sh)
	{
	case 1:
		sun->addXKey(-205);//целевая точка
		sun->addYKey(91);//целевая точка
	break;
	case 2:
		sun->addXKey(-193);//целевая точка
		sun->addYKey(93);//целевая точка
	break;
	case 3:
		sun->addXKey(-193);//целевая точка
		sun->addYKey(109);//целевая точка
	break;
	case 4:
		sun->addXKey(-193);//целевая точка
		sun->addYKey(132);//целевая точка
	break;
	}//switch
	sun->ComputeX();
	sun->ComputeY();
sun->SetFall(true);
}

void Level::GoDown(Ruby *t)//опускает находящиеся сверху фишки вниз
{
vector <Ruby*>::iterator r = rubyvec.begin();
while (r != rubyvec.end())
{
if ((*r != NULL) && ((*r)->GetXpos() == t->GetXpos()) && ((*r)->GetYpos() <= t->GetYpos() - cellSize))//Look Out!!!
{
(*r)->SetFall(true);

for (int i = 1; i <= 11; i++)//Look Out!!!
{
bool b = false;
vector <Cell*>::iterator it = cellvec.begin();
while (it != cellvec.end())
{
if ((*r != NULL) && ((*r)->GetXpos() == (*it)->GetXpos()) && ((*r)->GettarY() + cellSize * i == (*it)->GetYpos()))
{
b = true;
break;
}//if
it++;
}//while
if (b && (*r != NULL)) 
{
(*r)->SettarY((*r)->GettarY() + cellSize * i);
break;
}//if
}//for

}//if
r++;
}//while

vector <SunPart*>::iterator s = sunvec.begin();
while (s != sunvec.end())
{
if ((*s != NULL) && ((*s)->GetXpos() == t->GetXpos()) && ((*s)->GetYpos() <= t->GetYpos() - cellSize))//Look Out!!!
{
(*s)->SetFall(true);

for (int i = 1; i <= 11; i++)
{
bool b = false;
vector <Cell*>::iterator it = cellvec.begin();
while (it != cellvec.end())
{
if ((*s != NULL) && ((*s)->GetXpos() == (*it)->GetXpos()) && ((*s)->GettarY() + cellSize * i == (*it)->GetYpos()))
{
b = true;
break;
}//if
it++;
}//while
if (b && (*s != NULL)) 
{
(*s)->SettarY((*s)->GettarY() + cellSize * i);
break;
}//if
}//for

}//if
s++;
}//while
}

void Level::Create_Labs(int i, float x, float y)
{
int z = 0;
if (i == 3)
{
 score->Add(15);
 z = 15;
} else
if (i == 4) 
{
 score->Add(40);
 z = 40;
} else
if (i >= 5)
{
 score->Add(75);
 z = 75;
}
if (z != 0)
{
Font *lab = new Font(gFont, Hge->Timer_GetTime(), z, Xpos + x, Ypos + y, 0.8f);
scorelabs.push_back(lab);
if (scorelabs.size() > 1)
{
Font *xrow = new Font(gFont, Hge->Timer_GetTime(), scorelabs.size(), Xpos + x, Ypos + y - cellSize, 1.0f);
xrowlabs.push_back(xrow);
}//if
}//if
}

void Level::CheckToDelete()//удаление фишек
{
int i = 0;
float x = 0, y = 0;
vector <Ruby*>::iterator t = rubyvec.begin();
while (t != rubyvec.end())
{
if (((*t) != NULL) && (!(*t)->GetRemoved()) && (((*t)->GetHRem()) || ((*t)->GetVRem())))
{
i++;
if ((x == 0) && (y ==0))
{
x = (*t)->GetXpos() + cellSize / 2;
y = (*t)->GetYpos() + cellSize / 2;
}
DoIt(*t);
} 
t++;
}//while
Create_Labs(i, x, y);
}

void Level::DoIt(Ruby *t)
{
if (!t->GetLock())
{
GoDown(t);
Create_Dib(t->GetXpos());
t->SetRemoved(true);
}//if
else
{
t->SetLock(false);
t->SetHRem(false);
t->SetVRem(false);
}//else
}

void Level::Create_Dib(float xpos)//создает новую фишку
{
Ruby *ruby;
int rnum = Hge->Random_Int(0, 4) + 2;
int Up = 999;
vector <Cell*>::iterator iter = cellvec.begin();
while (iter != cellvec.end())
{//ищем самую верхнюю половую ячейку в текущем столбце :)
if (((*iter)->GetXpos() == xpos) && ((*iter)->GetYpos() < Up)
&& ((*iter)->GetYpos() >= 0))//перестрахуемся :)
Up = (*iter)->GetYpos();
iter++;
}

			if (rnum == truby)
			{
			ruby = new Ruby(&rubyTex, truby, number, xpos, Up - cellSize);
			} else
			if (rnum == tgold)
			{
			ruby = new Ruby(&goldTex, tgold, number, xpos, Up - cellSize);
			} else
			if (rnum == thelmet)
			{
			ruby = new Ruby(&helmetTex, thelmet, number, xpos, Up - cellSize);
			} else
			if (rnum == tgreensun)
			{
			ruby = new Ruby(&greensunTex, tgreensun, number, xpos, Up - cellSize);
			} else
			if (rnum == tseashell)
			{
			ruby = new Ruby(&seashellTex, tseashell, number, xpos, Up - cellSize);
			}
			ruby->SettarY(Up);
			ruby->SetFall(true);
			rubyvec.push_back(ruby);
}

bool Level::CheckCompositions(Ruby *ruby)//проверяет составляют ли фишки композицию
{
int hhit = 0, vhit = 0;
vector <Ruby*> rubhor;//2 вектора, чтобы заполнить их за один проход по 
vector <Ruby*> rubver;//вектору фишек
vector <Ruby*>::iterator iter = rubyvec.begin();
bool l = false, r = false, ll = false, rr = false, back = false;
while (iter != rubyvec.end())
{
if (((&ruby) != NULL) && ((&iter) != NULL) && ((*iter)->GetType() == ruby->GetType()))
{
if ((*iter)->GetYpos() == ruby->GetYpos())
rubhor.push_back(*iter);
if ((*iter)->GetXpos() == ruby->GetXpos())
rubver.push_back(*iter);
}//if
iter++;
}//while

//проверка на горизонтальную композицию
if (rubhor.size() >= 3)
{
vector <Ruby*>::iterator ter = rubhor.begin();
while (ter != rubhor.end())
{
if ((*ter)->GetXpos() == ruby->GetXpos() - cellSize) 
{
l = true;
(*ter)->SetHRem(true);
hhit++;
}
if ((*ter)->GetXpos() == ruby->GetXpos() + cellSize) 
{
r = true;
(*ter)->SetHRem(true);
hhit++;
}
ter++;
}//while
ter = rubhor.begin();
while (ter != rubhor.end())
{
if (((*ter)->GetXpos() == ruby->GetXpos() - cellSize - cellSize) && (l)) 
{
ll = true;
(*ter)->SetHRem(true);
hhit++;
}
if (((*ter)->GetXpos() == ruby->GetXpos() + cellSize + cellSize) && (r)) 
{
rr = true;
(*ter)->SetHRem(true);
hhit++;
}
ter++;
}//while
if (((l) && (ll)) || ((r) && (rr)) || ((l) && (r)))  
{
hhit++;
ruby->SetHRem(true);
}//if
if (hhit < 3) 
{
vector <Ruby*>::iterator ter = rubhor.begin();
ter = rubhor.begin();
while (ter != rubhor.end())
{
(*ter)->SetHRem(false);
ter++;
}//while
}//if
}//if

//проверка на вертикальную композицию
l = false;
r = false;
ll = false;
rr = false;
if (rubver.size() >= 3)
{
vector <Ruby*>::iterator ter = rubver.begin();
while (ter != rubver.end())
{
if ((*ter)->GetYpos() == ruby->GetYpos() - cellSize) 
{
l = true;
(*ter)->SetVRem(true);
vhit++;
}
if ((*ter)->GetYpos() == ruby->GetYpos() + cellSize) 
{
r = true;
(*ter)->SetVRem(true);
vhit++;
}
ter++;
}//while
ter = rubver.begin();
while (ter != rubver.end())
{
if (((*ter)->GetYpos() == ruby->GetYpos() - cellSize - cellSize) && (l)) 
{
ll = true;
(*ter)->SetVRem(true);
vhit++;
}
if (((*ter)->GetYpos() == ruby->GetYpos() + cellSize + cellSize) && (r)) 
{
rr = true;
(*ter)->SetVRem(true);
vhit++;
}
ter++;
}//while
if (((l) && (ll)) || ((r) && (rr)) || ((l) && (r))) 
{
vhit++;
ruby->SetVRem(true);
}//if
if (vhit < 3) 
{
vector <Ruby*>::iterator ter = rubver.begin();
ter = rubver.begin();
while (ter != rubver.end())
{
(*ter)->SetVRem(false);
ter++;
}//while
}//if
}//if

if ((hhit > 2) || (vhit > 2)) back = true;
return back;
}

/*
void Level::CheckMouseMove(float Xcur, float Ycur, float thisTime)
{
//ruby
	const float longdelay = 2.5f;
	static long lastTime = 0;
	static int dibnum = -1;//номер фишки

vector <Ruby>::iterator ter = rubyvec.begin();
while (ter != rubyvec.end())
{
		if ((!ter->GetLock()) && (ter->CheckMousePos(Xcur-Xpos, Ycur-Ypos)) && (ter->GetActivity() == do_shine)
			&& ((dibnum != ter->GetNum()) || (thisTime - lastTime > longdelay)))
		{// движение мыши - блеск :)
			dibnum = ter->GetNum();
			ter->Shine_Play();
			lastTime = thisTime;
		} 
ter++;
}
}
*/

void Level::CheckMouseMoveOverload(float Xcur, float Ycur, float thisTime)
{
const float longdelay = 2.5f;
static long lastTime = thisTime;
static int dibnum = -1;//номер фишки

int x = (int)(Xcur - Xpos);
int y = (int)(Ycur - Ypos);
while (x % cellSize != 0) x--;
while (y % cellSize != 0) y--;

vector <Ruby*>::iterator iter = rubyvec.begin();
while (iter != rubyvec.end())
{
if ((!(*iter)->GetLock()) && ((*iter)->GetActivity() == do_shine)
&& ((*iter)->GetXpos() == x) && ((*iter)->GetYpos() == y) &&
((dibnum != (*iter)->GetNum()) || (thisTime - lastTime > longdelay)))
{
(*iter)->Shine_Play();
dibnum = (*iter)->GetNum();
lastTime = thisTime;
}//if
iter++;
}//while
}

void Level::CheckMouseDown(float Xcur, float Ycur, float thisTime)
{
//ruby
static float lastTime = 0.0f;
vector <Ruby*>::iterator ter = rubyvec.begin();
while (ter != rubyvec.end())
{
	if ((!(*ter)->GetLock()) && ((*ter)->CheckMousePos(Xcur - Xpos, Ycur - Ypos)) &&
		((*ter)->GetActivity() == do_shine))
	{// щелчок мышью по блестящей фишки - начинает крутиться 
		//очищаю вектора с надписями
		if (scorelabs.size() > 0) {
		for (int i = 0; i < scorelabs.size(); ++i) {
			delete scorelabs[i];
		}
		scorelabs.clear();
	}
	if (xrowlabs.size() > 0) {
		for (int i = 0; i < xrowlabs.size(); ++i) {
			delete xrowlabs[i];
		}
		xrowlabs.clear();
	}
		////////////////////////////
			lastTime = thisTime;         // Look Out!!!
			if (pRuby1 != NULL)
			{
				if ((pRuby1->GetYpos() == (*ter)->GetYpos())
				&& ((pRuby1->GetXpos() + cellSize == (*ter)->GetXpos())
				|| (pRuby1->GetXpos() - cellSize == (*ter)->GetXpos())))
				{//соседи по Х, значит надо поменять их местами
				pRuby2 = (*ter);
				pRuby2->SettarX(pRuby1->GetXpos());
				pRuby1->SettarX(pRuby2->GetXpos());
				pRuby2->SettarY(pRuby1->GetYpos());
				pRuby1->SettarY(pRuby2->GetYpos());
				start_moving = true;
				 }	else//соседи по Y
				 if ((pRuby1->GetXpos() == (*ter)->GetXpos())
				&& ((pRuby1->GetYpos() + cellSize == (*ter)->GetYpos())
				|| (pRuby1->GetYpos() - cellSize == (*ter)->GetYpos()))) 
				{//соседи по Y, значит надо поменять их местами
				pRuby2 = (*ter);
				pRuby2->SettarY(pRuby1->GetYpos());
				pRuby1->SettarY(pRuby2->GetYpos());
				pRuby2->SettarX(pRuby1->GetXpos());
				pRuby1->SettarX(pRuby2->GetXpos());
				start_moving = true;
				} else//не соседи
				if (pRuby1 != NULL)//прошлая фишка выбрана
				{		
				pRuby1->Spin_Stop();
				pRuby1 = NULL;
				}
		     } else
			if (pRuby1 == NULL)//если прошлая фишка не выбрана
			{
			pRuby1 = NULL;
			pRuby2 = NULL;
			pRuby1 = (*ter);
			if (pRuby1->GetType() != tsunpart)
			pRuby1->Spin_Play();
			}
		} else// равен сам себе, останавливаем вращаение
		if ((pRuby1 != NULL) && 
		((*ter)->CheckMousePos(Xcur-Xpos, Ycur-Ypos)) &&
		((*ter)->GetActivity() == do_spin))
		{
			if (pRuby1->GetType() != tsunpart)
			pRuby1->Spin_Stop();
			pRuby1 = NULL;
			pRuby2 = NULL;
		} else//кликнуто на свободном от фишек поле
		if ((pRuby1 != NULL) &&
		   (!(*ter)->CheckMousePos(Xcur-Xpos, Ycur-Ypos)) &&
		((*ter)->GetActivity() == do_spin) && (thisTime - lastTime > 0.5f))
		{
			if (pRuby1->GetType() != tsunpart)
			pRuby1->Spin_Stop();
//			pRuby1 = NULL;
			lastTime = thisTime;
		}
ter++;
}
// разные объекты находятся в разных векторах, 
// поэтому надо повторить процедуру нахождения 
// координат курсора второй раз
//sunpart 
vector <SunPart*>::iterator tr = sunvec.begin();
if (pRuby2 == NULL)
while (tr != sunvec.end())
{
		if ((*tr)->CheckMousePos(Xcur-Xpos, Ycur-Ypos))
		{
			lastTime = thisTime;         // Look Out!!!
			if (pRuby1 != NULL) 
			{
				if ((pRuby1->GetYpos() == (*tr)->GetYpos())
				&& ((pRuby1->GetXpos() + cellSize == (*tr)->GetXpos())
				|| (pRuby1->GetXpos() - cellSize == (*tr)->GetXpos())))
				{//соседи по Х, значит надо поменять их местами
				pRuby2 = (*tr);
				pRuby2->SettarX(pRuby1->GetXpos());
				pRuby1->SettarX(pRuby2->GetXpos());
				pRuby2->SettarY(pRuby1->GetYpos());
				pRuby1->SettarY(pRuby2->GetYpos());
				start_moving = true;
				 }	else//соседи по Y
				 if ((pRuby1->GetType() != tsunpart) &&
				 (pRuby1->GetXpos() == (*tr)->GetXpos())
				&& ((pRuby1->GetYpos() + cellSize == (*tr)->GetYpos())
				|| (pRuby1->GetYpos() - cellSize == (*tr)->GetYpos())))
				{//соседи по Y, значит надо поменять их местами
				pRuby2 = (*tr);
				pRuby2->SettarY(pRuby1->GetYpos());
				pRuby1->SettarY(pRuby2->GetYpos());
				pRuby2->SettarX(pRuby1->GetXpos());
				pRuby1->SettarX(pRuby2->GetXpos());
				start_moving = true;
				} else//не соседи
				if (pRuby1 != NULL) //прошлая фишка выбрана
				{		
				pRuby1->Spin_Stop();
				pRuby1 = NULL;
				}
		     } else
			if (pRuby1 == NULL)//если прошлая фишка не выбрана
			{
			pRuby1 = NULL;
			pRuby2 = NULL;
			pRuby1 = (*tr);
			}
		} else// равен сам себе, останавливаем вращаение
		if ((pRuby1 != NULL) &&
		((*tr)->CheckMousePos(Xcur-Xpos, Ycur-Ypos)))
		{
			pRuby1 = NULL;
			pRuby2 = NULL;
		} else//кликнуто на свободном от фишек поле
		if ((pRuby1 != NULL) && 
		   (!(*tr)->CheckMousePos(Xcur-Xpos, Ycur-Ypos)) &&
		   (thisTime - lastTime > 0.5f))
		{
			pRuby1->Spin_Stop();
//			pRuby1 = NULL;
			lastTime = thisTime;
		}
tr++;
}

}