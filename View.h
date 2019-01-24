#ifndef _H_VIEW
#define _H_VIEW

#include <windows.h>
#include "world.h"
#include "lib\other\bitmap.h"

class CView
{
public:
	CView();
	~CView();

	void Create	(HINSTANCE hInstance, CWorld * world);
	void Size	(int width, int height);
	void Update	(Canvas & canvas);
	void Paint	(Canvas & canvas);

	RECT _client, _game;

private:
	Bitmap _bmpBack;

	HPEN _hpenCircle, _hpenPlayer[2], _hpenBall;

	CWorld* _world;

	int _width, _height;
};

#endif