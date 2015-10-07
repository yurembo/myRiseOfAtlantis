#include "sunpart.h"

SunPart::SunPart()
{
//Ruby();
	num = 0;
	Xpos = 0;
	Ypos = 0;

	type = 0;
	tarX = 0;
	tarY = 0;
	hrem = false;
	vrem = false;
	go_back = false;
	fall = false;
	removed = false;
	onPlace = false;
	doFire = false;

	spr = NULL;
	suntex = NULL;

	partsys = NULL;
	partsystex = NULL;
	partsysspr = NULL;

	name = 0;
	time = 0;

	spx.Clear();
	spy.Clear();
}

SunPart::SunPart(short Name, HGE *hge, const char* pathTex, int typ, int inum, float x, float y)
{
//Ruby();
	num = inum;
	name = Name;
	Xpos = x;
	Ypos = y;
	type = typ;

	tarX = x;
	tarY = y;
	hrem = false;
	vrem = false;
	go_back = false;
	fall = false;
	removed = false;
	onPlace = false;
	doFire = false;
	time = 0;

	spx.Clear();
	spy.Clear();

	Hge = hge;
	suntex = Hge->Texture_Load(pathTex);
	spr = new hgeSprite(suntex, x, y, float(sunSize), float(sunSize));	
	spr->SetTextureRect(4, 15, float(sunSize / 2 + 15), float(sunSize));

	partsystex = Hge->Texture_Load("Data//particles.png");

	partsysspr = new hgeSprite(partsystex, 32, 32, 32, 32);
	partsysspr->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	partsysspr->SetHotSpot(-16, -16);

	partsys = new hgeParticleSystem("Data//trail.psi", partsysspr);
}

SunPart::SunPart(const SunPart& sunpart)
{
	num = sunpart.num;
	name = sunpart.name;
	Xpos = sunpart.Xpos;
	Ypos = sunpart.Ypos;
	spr = sunpart.spr;
	suntex = sunpart.suntex;

	type = sunpart.type;
	tarX = sunpart.tarX;
	tarY = sunpart.tarY;
	hrem = sunpart.hrem;
	vrem = sunpart.vrem;
	go_back = sunpart.go_back;
	fall = sunpart.fall;
	removed = sunpart.removed;
	onPlace = sunpart.onPlace;
	time = sunpart.time;
	doFire = sunpart.doFire;

	spx = sunpart.spx;
	spy = sunpart.spy;

	partsystex = sunpart.partsystex;
	partsysspr = sunpart.partsysspr;
	partsys = sunpart.partsys;
}

SunPart::~SunPart()
{
	num = 0;
	Xpos = 0;
	Ypos = 0;
	name = 0;

	type = 0;
	tarX = 0;
	tarY = 0;
	hrem = false;
	vrem = false;
	go_back = false;
	fall = false;
	removed = false;
	onPlace = false;
	time = 0;
	doFire = false;

	spx.Clear();
	spy.Clear();

	delete spr;
	spr = NULL;

	Hge->Texture_Free(suntex);

	delete partsys;
	partsys = NULL;
	delete partsysspr;
	partsysspr = NULL;

	Hge->Texture_Free(partsystex);
}

SunPart& 
SunPart::operator=(const SunPart& sunpart)
{
	if (this == &sunpart)//проверка: не равен ли сам себе :)
	return *this;
	if (&sunpart != NULL)
	{
	num = sunpart.num;
	name = sunpart.name;
	Xpos = sunpart.Xpos;
	Ypos = sunpart.Ypos;
	type = sunpart.type;
	tarX = sunpart.tarX;
	tarY = sunpart.tarY;
	hrem = sunpart.hrem;
	vrem = sunpart.vrem;
	go_back = sunpart.go_back;
	fall = sunpart.fall;
	removed = sunpart.removed;
	onPlace = sunpart.onPlace;
	suntex = sunpart.suntex;
	spr = sunpart.spr;
	time = sunpart.time;
	doFire = sunpart.doFire;

	spx = sunpart.spx;
	spy = sunpart.spy;

	partsystex = sunpart.partsystex;
	partsysspr = sunpart.partsysspr;
	partsys = sunpart.partsys;
	}
	return *this;
}


bool SunPart::Render(float x, float y)
{
	if (removed)
	{
		time += 0.002f;
		Xpos = spx.getGlobalFrame(time);
		Ypos = spy.getGlobalFrame(time);

			partsys->info.nEmission=(5000);
			partsys->MoveTo(x + Xpos,y + Ypos);
			partsys->Update(0.01f);

			if (partsys != NULL) partsys->Render();

		if (!doFire) 
		{
		doFire = true;
		partsys->Fire();//Look Out!!!
		}

		if (time >= 1.0f) 
		{
			partsys->Stop();
			removed = false;
			onPlace = true;
		}
	}
	spr->Render(x+Xpos, y+Ypos);

return false;
}

bool SunPart::CheckMousePos(float Xcur, float Ycur)
{
	bool insert = false;// в проверяемой области
	hgeRect *rect = new hgeRect();
	
	spr->GetBoundingBoxEx(Xpos, Ypos, 0.0, 1.0, 1.0, rect);
	insert = rect->TestPoint(Xcur, Ycur);

return insert;
}

bool SunPart::Move()
{
const float g = 1.0f;
if (Xpos < tarX)
{
Xpos += g; 
} else 
if (Xpos > tarX)
{
Xpos -= g;
}

if (Ypos < tarY)
{
Ypos += g; 
}else 
if (Ypos > tarY)
{
Ypos -= g;
}

bool b = true;
if ((Xpos + g >= tarX - g) && (Xpos - g <= tarX + g) 
&& (Ypos + g >= tarY - g) && (Ypos - g <= tarY + g))
{
Xpos = tarX;
Ypos = tarY;
b = false;
}
return b;
}
