#include "font.h"

Font::Font()
{
	num = 0;
	Xpos = 0;
	Ypos = 0;
	score = 0;
	tarscore = 0;
	font = NULL;
	mult = 0;
	TimeToBorn = 0;
	visible = true;
}

Font::Font(hgeFont *f, float time, int sc, float xpos, float ypos, float mul)
{
	num = 0;
	score = sc;
	tarscore = sc;
	Xpos = xpos;
	Ypos = ypos;
	font = f;
	mult = mul;
	TimeToBorn = time;
	visible = true;
}

Font::Font(const Font& ffont)
{
	num = ffont.num;
	score = ffont.score;
	tarscore = ffont.tarscore;
	Xpos = ffont.Xpos;
	Ypos = ffont.Ypos;
	font = ffont.font;
	mult = ffont.mult;
	TimeToBorn = ffont.TimeToBorn;
	visible = ffont.visible;
}

Font::~Font()
{
	num = 0;
	score = 0;
	tarscore = 0;
	Xpos = 0;
	Ypos = 0;
//	delete font;
	font = NULL;
	mult = 0;
	TimeToBorn = 0;
	visible = false;
}

void Font::Render(int mode, float thisTime)
{
static float lastTime = 0;

if (visible)
{
if ((score < tarscore) && (thisTime - lastTime > 0.01))
{
 score++;
 lastTime = thisTime;
}

if (mult <= 1.0f) 
{
	Ypos -= 0.1f;
	mult -= 0.001f;
	if (thisTime - TimeToBorn > 2.0f) visible = false;
}

font->SetScale(mult);

switch (mode)
{
case 0:
	font->printf(Xpos, Ypos, HGETEXT_RIGHT, "%d", score);
	break;
case 1:
	font->printf(Xpos, Ypos, HGETEXT_RIGHT, "%s%d", "+", score);
	break;
case 2:
	font->printf(Xpos, Ypos, HGETEXT_RIGHT, "%s%d", "x", score);
	break;
}//switch
}//if
}

void Font::Add(int num)
{
	tarscore += num;
}