#include "game.h"
#include <assert.h>
#include <stdlib.h>
#include <windows.h>

const bool bMoveShape[3][3] = 
{
	{ 0, 1, 0 },
	{ 1, 1, 1 },
	{ 0, 1, 0 }
};

CLightsGame::CLightsGame() : _bGameover(0) 
{ 
}

void CLightsGame::New()
{
	srand(GetTickCount());

	_iPerfectMoves = 0;

	for (int x = 0; x < Width(); x++)
	{
		for (int y = 0; y < Height(); y++)
		{
			if (rand()%2)
			{
				Move(x, y);
				_iPerfectMoves++;
			}
		}
	}

	_iMoves = 0;
}

void CLightsGame::Move(int x, int y)
{
	// Combine move with history
	_record.Toggle(x, y);

	// Relocate to upper-left
	x--;
	y--;
	for (int b = 0; b < 3; b++)
	{
		for (int a = 0; a < 3; a++)
		{
			if (bMoveShape[a][b])
			{
				if (InBounds(x + a, y + b))
				{
					Toggle(x + a, y + b);
				}
			}
		}
	}

	_iMoves++;

	if (NumberOff() == Tiles())
		End();
}

void CLightsGame::Hint(int& rx, int& ry)
{
	POINT* array = new POINT[Tiles()];
	int    items = 0;

	int x=0, y=0;

	for (int i = 0; i < Tiles(); i++)
	{
		if (_record.Get(i) == true)
		{
			array[items].x = x;
			array[items].y = y;
			items++;
		}

		x++;
		if (x >= Width())
		{
			x = 0;
			y++;
		}
	}

	int index = rand() % items;
	rx = array[index].x;
	ry = array[index].y;
}

int CLightsGame::GetMovesLeft()
{
	int count=0;
	for (int i = 0; i < Tiles(); i++)
	{
		if (_record.Get(i) == true)
		{
			count++;
		}
	}

	return count;
}

int CLightsGame::NumberOn()
{
	int count = 0;
	for (int i = 0; i < Width() * Height(); i++)
	{
		if (Get(i) == TILE_ON)
			count++;
	}

	return count;
}

int CLightsGame::NumberOff()
{
	int count = 0;
	for (int i = 0; i < Width() * Height(); i++)
	{
		if (Get(i) == TILE_OFF)
			count++;
	}

	return count;
}

void CBoard::Create(int width, int height)
{
	if (_board != 0)
		Free();

	_width  = width;
	_height = height;
	_right  = width - 1;
	_bottom = height - 1;

	_board = new bool[width * height];
	Clear();
}

void CBoard::Free()
{
	assert(_board != 0);

	delete _board;
	_board = 0;
}