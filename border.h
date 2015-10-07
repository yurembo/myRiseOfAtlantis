#include "cell.h"

class Border : public Cell
{
protected:
	hgeSprite *spr;
	float rot;
public:
	Border();//default constructor
	Border(HTEXTURE *tex, int n, float xtex, float ytex, float xpos, float ypos, float rotate);//constructor with parameters
	Border(const Border& cell);//copy constructor
	~Border();//destructor

	void Render(float x, float y);
};