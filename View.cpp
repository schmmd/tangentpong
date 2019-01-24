#include "view.h"
#include "lib\other\canvas.h"
#include "main.h"
#include "resource.h"

#include <stdio.h>

CView::CView()
{
	_hpenCircle    = CreatePen(PS_SOLID, CIRCLE_WIDTH, RGB(000,000,000));
	_hpenPlayer[0] = CreatePen(PS_SOLID, CIRCLE_WIDTH + 2, RGB(000,200,000));
	_hpenPlayer[1] = CreatePen(PS_SOLID, CIRCLE_WIDTH + 2, RGB(000,000,200));
	_hpenBall	   = CreatePen(PS_SOLID, 7, RGB(200,000,000));
}

CView::~CView()
{

}

void CView::Create	(HINSTANCE hInstance, CWorld * world)
{
	_world = world;
}

void CView::Size	(int width, int height)
{
	_width  = width;
	_height = height;

	_client.left   = 0;
	_client.right  = width;
	_client.top    = 0;
	_client.bottom = height;

	CopyRect(&_game, &_client);

	_game.left   += GAME_BORDER;
	_game.right  -= GAME_BORDER;
	_game.top    += GAME_BORDER;
	_game.bottom -= GAME_BORDER;
}

void CView::Update	(Canvas & canvas)
{
	if (_width == 0 || _height == 0)
		return;

    Bitmap bmp (canvas, _width, _height);
    BitmapCanvas bmpCanvas (canvas, bmp);

	bmpCanvas.WhiteWash(_client);
	bmpCanvas.SelectObject(_hpenCircle);
	bmpCanvas.Ellipse(_game.left, _game.top, _game.right, _game.bottom);

	if (_world->IsPlaying())
	{
		for (int i = 0; i < 2; i++)
		{
			bmpCanvas.SelectObject(_hpenPlayer[i]);
			bmpCanvas.Line(xOffset + _world->_paddle[i].GetX1(), yOffset + -1 * _world->_paddle[i].GetY1(), xOffset + _world->_paddle[i].GetX2(), yOffset + -1 * _world->_paddle[i].GetY2());

			/*
			bmpCanvas.Arc(_game.left, _game.top, _game.right, _game.bottom, 
				xOffset + _world->_paddle[i].GetX1(), yOffset + _world->_paddle[i].GetY1(), xOffset + _world->_paddle[i].GetX2(), yOffset + _world->_paddle[i].GetY2());
			*/
		}

		bmpCanvas.Ellipse(xOffset + _world->_ball.GetX1(), yOffset + -1 * _world->_ball.GetY1(), xOffset + _world->_ball.GetX2(), yOffset + -1 * _world->_ball.GetY2());
			// bmpCanvas.Ellipse(_world->_paddle.GetX(), _world->_paddle.GetY(), _world->_paddle.GetX() + 5, _world->_paddle.GetY() + 5);
	}

	_bmpBack = bmp;
}

void CView::Paint	(Canvas & canvas)
{
	if (_width == 0 || _height == 0)
		return;

	Blitter bltBack(_bmpBack);
	bltBack.BlitTo (canvas);
}