#ifndef _H_WORLDOBJECTS
#define _H_WORLDOBJECTS

#include <math.h>
#include "main.h"

class CPaddle
{
public:
	void SetWidth(float width) { _halfwidth = width / 2; }

	float GetHalfWidth() { return _halfwidth; }

	void SetRadians(double radians)
	{
		if (radians < 0)
			radians += 2 * PI;
		else if (radians > 2 * PI)
			radians -= 2 * PI;

		_radians = radians;

		// Calcualate angle of tangent
		double theta = radians + PI / 2;

		// Calculate the intersection point
		int x = int(double(radius) * cos(radians));
		int y = int(double(radius) * sin(radians));

		// Calculate the slope of the tangent
		// Formula derived with Calculus
		double m = x / sqrt(pow(radius, 2) - pow(x, 2));

		// Adjust slope (sign is off)
		if (radians > PI)
			m = -m;

		// Solve for start and end points of the line
		_x1 = x + int(double(_halfwidth) * cos(theta));
		_y1 = y + int(double(_halfwidth) * sin(theta));
		_x2 = x - int(double(_halfwidth) * cos(theta));
		_y2 = y - int(double(_halfwidth) * sin(theta));

		/*
		_x1 = (int((double)radius * (double)cos(radians + _halfwidth)));
		_y1 = (int((double)radius * (double)sin(radians + _halfwidth)));
		_x2 = (int((double)radius * (double)cos(radians - _halfwidth)));
		_y2 = (int((double)radius * (double)sin(radians - _halfwidth)));
		*/
	}

	void GetLoc(double radians, double& x, double& y)
	{
		x = radius * cos(radians);
		y = radius * sin(radians);
	}

	void Clockwise(double step)
	{
		SetRadians(_radians - step);
	}

	void Counterwise(double step)
	{
		SetRadians(_radians + step);
	}

	double LRadianBound() { return _radians - _halfwidth; }
	double URadianBound() { return _radians + _halfwidth; }

	int GetX1() { return _x1; }
	int GetY1() { return _y1; }
	int GetX2() { return _x2; }
	int GetY2() { return _y2; }

private:
	int _x1, _y1, _x2, _y2;
	double _radians;
	double _halfwidth;
};

class CBall
{
public:
	void Move()
	{
		SetLoc(_x + _cx, _y + _cy);
	}

	void SetDir(float cx, float cy) { _cx = cx; _cy = cy; }
	void SetLoc(float x , float y )
	{
		_x = x;
		_y = y;
		_degrees = atan2(_y, _x);
	}

	void SetRadius(int radius) { _radius = radius; }
	int  GetRadius(			 ) { return _radius; }

	double GetRadians() { return _degrees; }

	int GetCenterX() { return (int)_x; }
	int GetCenterY() { return (int)_y; }
	float GetDX() { return _cx; }
	float GetDY() { return _cy; }
	int GetX1() { return GetCenterX() - _radius; }
	int GetY1() { return GetCenterY() - _radius; }
	int GetX2() { return GetCenterX() + _radius; }
	int GetY2() { return GetCenterY() + _radius; }
	
private:
	double _degrees;
	float _x, _y, _cx, _cy;
	int _radius;
};

#endif