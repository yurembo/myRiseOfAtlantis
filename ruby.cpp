#include "ruby.h"

Ruby::Ruby()
{
	num = 0;
	Xpos = 0;
	Ypos = 0;
	type = 0;
	activity = NULL;
	tarX = 0;
	tarY = 0;
	fall_times = 0;
	hrem = false;
	vrem = false;
	go_back = false;
	fall = false;
	lock = false;
	linklock = NULL;
	removed = false;
	time = 0;

	shine_anim = NULL;
	spin_anim = NULL;
}

Ruby::Ruby(HTEXTURE *tex, int typ, int n, float x, float y)
{
	num = n;
	Xpos = x;
	Ypos = y;
	type = typ;
	activity = do_shine;
	tarX = x;
	tarY = y;
	fall_times = 0;
	hrem = false;
	vrem = false;
	go_back = false;
	fall = false;
	lock = false;
	linklock = NULL;
	removed = false;
	time = 0;

	shine_anim = new hgeAnimation(*tex, 36, 150.0f, 0.0f, 120.0f, float(cellSize), float(cellSize));
	shine_anim->SetMode(HGEANIM_FWD | HGEANIM_NOLOOP);

	spin_anim = new hgeAnimation(*tex, 36, 150.0f, 0.0f, 0.0f, float(cellSize), float(cellSize));
	spin_anim->SetMode(HGEANIM_FWD | HGEANIM_LOOP);
}

Ruby::Ruby(const Ruby& ruby)
{
	num = ruby.num;
	Xpos = ruby.Xpos;
	Ypos = ruby.Ypos;
	type = ruby.type;
	activity = ruby.activity;
	tarX = ruby.tarX;
	tarY = ruby.tarY;
	fall_times = ruby.fall_times;
	hrem = ruby.hrem;
	vrem = ruby.vrem;
	go_back = ruby.go_back;
	fall = ruby.fall;
	lock = ruby.lock;
	linklock = ruby.linklock;
	removed = ruby.removed;
	time = ruby.time;

	shine_anim = ruby.shine_anim;
	spin_anim = ruby.spin_anim;
}

Ruby& 
Ruby::operator=(const Ruby& ruby)
{
	if (this == &ruby)//проверка: не равен ли сам себе :)
	return *this;
	if (&ruby != NULL)
	{
	num = ruby.num;
	Xpos = ruby.Xpos;
	Ypos = ruby.Ypos;
	type = ruby.type;
	activity = ruby.activity;
	tarX = ruby.tarX;
	tarY = ruby.tarY;
	fall_times = ruby.fall_times;
	hrem = ruby.hrem;
	vrem = ruby.vrem;
	go_back = ruby.go_back;
	fall = ruby.fall;
	lock = ruby.lock;
	linklock = ruby.linklock;
	removed = ruby.removed;
	time = ruby.time;

	shine_anim = ruby.shine_anim;
	spin_anim = ruby.spin_anim;
	}
	return *this;
}

Ruby::~Ruby()
{
	num = 0;
	Xpos = 0;
	Ypos = 0;
	type = 0;
	activity = 0;
	tarX = 0;
	tarY = 0;
	hrem = false;
	vrem = false;
	go_back = false;
	fall = false;
	lock = false;
	if (linklock != NULL) {
		delete linklock;
		linklock = NULL;
	}
	if (shine_anim != NULL) {
		delete shine_anim;
		shine_anim = NULL;
	}
	if (spin_anim != NULL) {
		delete spin_anim;
		spin_anim = NULL;
	}
	removed = false;
	time = 0;
}

bool Ruby::Render(float x, float y)
{
if (activity == do_shine)
{
	shine_anim->Update(0.002f);
	shine_anim->Render(x+Xpos, y+Ypos);
} else
if (activity == do_spin)
{
	spin_anim->Update(0.002f);
	spin_anim->Render(x+Xpos, y+Ypos);
}
if (linklock != NULL) linklock->Render(x, y);

if (removed)
{
	spin_anim->SetSpeed(50.0f);
	if (activity == do_shine) Spin_Play();
	Ypos += 0.25f;
	time += 0.0015f;
	if (time >= 1.0f) return true;
}

return false;
}

bool Ruby::CheckMousePos(float Xcur, float Ycur)
{
	bool insert = false;// в проверяемой области
	hgeRect *rect = new hgeRect();

	shine_anim->GetBoundingBoxEx(Xpos, Ypos, 0.0, 1.0, 1.0, rect);
	insert = rect->TestPoint(Xcur, Ycur);

return insert;
}

void Ruby::Shine_Play()
{
	shine_anim->Play();
	activity = do_shine;
}

void Ruby::Spin_Play()
{
	spin_anim->Play();
	activity = do_spin;
}

void Ruby::Spin_Stop()
{
	spin_anim->Stop();
	activity = do_shine;
}

bool Ruby::Move()
{
const float g = 1.0f;
if (Xpos < tarX)
{
Xpos += g; 
if (linklock != NULL) linklock->SetXpos(linklock->GetXpos() + g);
} else 
if (Xpos > tarX)
{
Xpos -= g;
if (linklock != NULL) linklock->SetXpos(linklock->GetXpos() - g);
}

if (Ypos < tarY)
{
Ypos += g; 
if (linklock != NULL) linklock->SetYpos(linklock->GetYpos() + g);
}else 
if (Ypos > tarY)
{
Ypos -= g;
if (linklock != NULL) linklock->SetYpos(linklock->GetYpos() - g);
}

bool b = true;
if ((Xpos + g >= tarX - g) && (Xpos - g <= tarX + g) 
&& (Ypos + g >= tarY - g) && (Ypos - g <= tarY + g))
{
Xpos = tarX;
Ypos = tarY;
//tarX = 0;
//tarY = 0;
if (linklock != NULL) linklock->SetXpos(Xpos);
if (linklock != NULL) linklock->SetYpos(Ypos);
b = false;
}
return b;
}

void Ruby::SetLock(bool l)
{
if (l) lock = l; else
if ((!l) && (lock) && (linklock != NULL)) 
{
lock = l;
linklock = NULL;
}
}
