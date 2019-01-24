#ifndef _H_WORLD
#define _H_WORLD

#include <windows.h>
#include "worldobjects.h"
#include "game.h"

const double step = .023;

class CWorld
{
public:
	CWorld() : _bPlaying(false) 
	{
		_paddle[0].SetWidth(50);
		_paddle[1].SetWidth(50);
	}

	void New();
	void Turn();

	bool IsPlaying() { return _bPlaying; }

	CPaddle _paddle[2];
	CBall   _ball;

private:
	bool _bPlaying;
};

#endif