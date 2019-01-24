#ifndef _H_GAME
#define _H_GAME

#include <memory.h>

const bool TILE_ON    = 1;
const bool TILE_OFF   = 0;

class CBoard
{
public:
	CBoard() : _board(0) {}

	void Create(int width, int height);
	void Clear() { memset(_board, 0, sizeof(bool) * _width * _height); }
	void Free();

	bool InBounds(int x, int y) { if (x >= 0 && y >= 0 && x < Width() && y < Height()) return true; else return false; }

	void Toggle(int x, int y) { int temp = y * _width + x; _board[temp] = !_board[temp]; }
	bool Get(int x, int y		 ) { return _board[y * _width + x]; }
	bool Get(int i)				   { return _board[i]; }
	void Set(int x, int y, bool v) { _board[y * _width + x] = v; }

	int Width () { return _width;  }
	int Height() { return _height; }
	int Tiles () { return _width * _height; }

	bool* _board;

private:
	int _width;
	int _height;
	int _right;
	int _bottom;
};

class CLightsGame : public CBoard
{
public:
	CLightsGame();

	void Create(int width, int height) { CBoard::Create(width, height); _record.Create(width, height); }

	void New ();
	void Move (int  x, int  y);
	void Hint (int& x, int& y);

	int NumberOn();
	int NumberOff();

	int GetMoves    () { return _iMoves; }
	int GetPerfect  () { return _iPerfectMoves; }
	int GetMovesLeft();

	void End()		  { _bGameover = true; }
	bool IsGameover() { return _bGameover; }

	CBoard _record;

private:
	bool _bGameover;
	int  _iMoves;
	int  _iPerfectMoves;
};

#endif