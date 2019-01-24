#include "world.h"
#include "main.h"

#include <assert.h>
#include <stdio.h>

#define KEYDOWN(vk_code) ((GetKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetKeyState(vk_code) & 0x8000) ? 0 : 1)

const int PPS = 6;

void CWorld::New()
{
	_paddle[0].SetRadians(0);
	_paddle[1].SetRadians(PI);
	_ball.SetLoc(0, 0);
	_ball.SetDir(PPS, 0);
	_ball.SetRadius(2);
	_bPlaying = true;
}

void CWorld::Turn()
{
	static DWORD dwStartTime = GetTickCount();

	if (GetTickCount() - dwStartTime > 100)
	{
		if (KEYDOWN(VK_LEFT))
		{
			_paddle[0].Counterwise(step);
		}
		if (KEYDOWN(VK_RIGHT))
		{
			_paddle[0].Clockwise(step);
		}
		if (KEYDOWN('A'))
		{
			_paddle[1].Counterwise(step);
		}
		if (KEYDOWN('D'))
		{
			_paddle[1].Clockwise(step);
		}
	}

	_ball.Move();

	// Calculate distance between the ball's center and the circle's center
	int distance = (int)sqrt(pow(_ball.GetCenterX(), 2) + pow(_ball.GetCenterY(), 2));

	// If the ball and circle touch
	// if (_ball.GetRadius() + distance >= radius - CIRCLE_WIDTH)
	{
		// Calculate degrees
		double radians = atan2(_ball.GetCenterY(), _ball.GetCenterX());

		float Bx = _ball.GetCenterX();
		float By = _ball.GetCenterY();

		float temp;

		for (int i = 0; i < 1; i++)
		{
			float P0x  = _paddle[i].GetX1();
			float P0y  = _paddle[i].GetY1();
			float P1x  = _paddle[i].GetX2();
			float P1y  = _paddle[i].GetY2();
/*
			if (P0y > P1y)
			{
				temp = P1y;
				P1y = P0y;
				P0y = temp;

				temp = P1x;
				P1x = P0x;
				P0x = temp;
			}
			*/
			float S2x = P1x - P0x;
			float S2y = P1y - P0y;

			float S1x = Bx;
			float S1y = By;

			float s = (-S1y * (Bx - P0x) + S1x * (By - P0y)) / (-S2x * S1y + S1x * S2y);
			float t = ( S2x * (By - P0y) - S2y * (Bx - P0x)) / (-S2x * S1y + S1x * S2y);

			float x = Bx + s * S2x;
			float y = By + s * S2y;

			if (s >= 0 && t >= 0 && s <= 1 && t <= 1)
			{
				temp = sqrt(pow(S2x, 2) + pow(S2y, 2));
				float nx = -S2y / temp;
				float ny = S2x / temp;

				temp = abs(x * nx + y * ny);
				float Nx = temp * nx;
				float Ny = temp * ny;

				float Fx = 2 * Nx + x;
				float Fy = 2 * Ny + y;

				float vx, vy;
				temp = sqrt(pow(Fx, 2) + pow(Fy, 2)) / PPS;
				if (temp == 0)
					vx = 0;
				else 
					vx = Fx / temp;

				if (temp == 0)
					vy = 0;
				else 
					vy = Fy / temp;
					

				_ball.SetDir(vx, vy);
			}
		}


		/*
		// If the ball is within the paddle's degrees
		if (_paddle[0].LRadianBound() < radians && _paddle[0].URadianBound() > radians)
		{



			_ball.SetDir(-1, -1);
		}
		*/
	}
}