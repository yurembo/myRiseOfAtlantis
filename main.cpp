// myRiseOfAtlantis   developed by Yazev Yuriy (on VC++ 6)
// BEGIN: 29.06.2009
// COMPLETE: 06.09.2009
// UPDATED to VC++ 2010: 01.09.2013

#include "level.h"

const int SCREEN_WIDTH = 800,
      SCREEN_HEIGHT = 600,
 	  SCREEN_BPP = 32;

HGE *hge = 0; //main object

HTEXTURE curTex; //текстуры
hgeSprite *cur; //спрайт для курсора

Level *level;

float Xcur, Ycur; //координаты курсора
bool pressed = false;// нажата ли кнопка
float thisTime = 0;// текущее время
int CanClick = 0;//можно ли совершить щелчок, имеет 3 значения: 0 - нельзя, 1 - можно, 2 - победа


bool LoadObjects()
{
	curTex = hge->Texture_Load("Data//cursor.png");
	if (!curTex) return false;

	level = new Level(hge, 335, 55);
	cur = new hgeSprite(curTex, 0, 0, 32, 32);

return true;
}

void DestroyObjects()
{
	hge->Texture_Free(curTex);
	delete cur;
	delete level;
	curTex = NULL;
}

bool FrameFunc()
{
hgeInputEvent event;
int type = 0, key = 0;

	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;

	if (hge->Input_GetEvent(&event))
	{
		Xcur = event.x;
		Ycur = event.y;
		type = event.type;
		key = event.key;
	}

	thisTime = hge->Timer_GetTime();
	if ((level != NULL) && (level->Get_StartGame())) level->CheckMouseMoveOverload(Xcur, Ycur, thisTime);

	if ((type == INPUT_MBUTTONDOWN) && (key == HGEK_LBUTTON))
	if ((CanClick == 1) && (level != NULL) && (!level->Get_StartMoving()))
	{
	level->CheckMouseDown(Xcur, Ycur, thisTime);
	}

	if (CanClick == 2)//перезапускаем игру - перезагружаем уровень
	{
		delete level;
		level = new Level(hge, 335, 55);
	}		

return false;
}

bool RenderFunc()
{
	// Render the scene
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	CanClick = level->Render(Xcur, Ycur, thisTime);
	cur->Render(Xcur, Ycur);
	hge->Gfx_EndScene();
	
	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)

{
  hge = hgeCreate(HGE_VERSION);
  hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
  hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
  hge->System_SetState(HGE_USESOUND, false);
  hge->System_SetState(HGE_FPS, 200);
  hge->System_SetState(HGE_WINDOWED, true);
  hge->System_SetState(HGE_SCREENWIDTH, SCREEN_WIDTH);
  hge->System_SetState(HGE_SCREENHEIGHT, SCREEN_HEIGHT);
  hge->System_SetState(HGE_SCREENBPP, SCREEN_BPP);
  hge->System_SetState(HGE_TITLE, "myRiseOfAtlantis   developed by Yazev Yuriy");
  if(hge->System_Initiate())
  {
	if (!LoadObjects())
		{
			MessageBox(NULL, LPCWSTR("Can't load objects"), LPCWSTR("Error"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}		
	// START!!!	 
    hge->System_Start();
	// destroying objects
	DestroyObjects();
  }
  else
  {	
    MessageBox(NULL, LPCWSTR(hge->System_GetErrorMessage()), LPCWSTR("Error"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
  }
  hge->System_Shutdown();
  hge->Release();
  return 0;
}


