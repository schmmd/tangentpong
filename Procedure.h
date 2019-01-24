#ifndef _H_PROC
#define _H_PROC

#include "lib\app.h"
#include "lib\timer.h"
#include "lib\other\timer.h"
#include "lib\menuitem.h"
#include "view.h"
#include "world.h"
#include "main.h"

#include <windows.h>

//
// Override some message handlers
//

class CGenericProc
{
	friend LRESULT CALLBACK CClass::Procedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetWindowHandle (HWND hwnd) { _hwnd = hwnd; }
public:
	virtual void Create (CREATESTRUCT * create) {}
	virtual bool Destroy () { return false; }
	virtual bool SysCommand (int cmd) { return false; }
	virtual bool Command (WORD wNotifyCode, WORD wID, HWND hwndCtrl) { return false; }
	virtual bool Size (int width, int height) { return false; }
	virtual bool Timer (int id, TIMERPROC * proc) { return false; }
	virtual bool MenuCommand (int cmdId, bool isAccel) { return false; }
	virtual bool CtrlCommand (int notifCode, int ctrlId, HWND hwnd) { return false; }
	virtual bool Paint (HDC hdc) { return false; }
	virtual bool LeftClick (int x, int y) { return false; }
	virtual bool KeyDown (int iVirtKey) { return false; }
protected:
	HWND _hwnd;
};

class CProcedure: public CGenericProc
{
public:
	CProcedure () 
		: _world (0), _iTileSizeRatio1(1), _iTileSizeRatio2(1)
	{}

	void Create (CREATESTRUCT * create);
	// bool SysCommand (int cmd);
	bool MenuCommand (int cmdId, bool isAccel);
	bool Destroy () { ::PostQuitMessage (0); return true; }
	bool Size (int width, int height);
	bool LeftClick(int x, int y);
	bool Paint (HDC hdc);

	void Exit () { ::DestroyWindow(_hwnd); }

	void UpdateAndPaint();

	CWorld*		_world;
	CView		_view;

private:

	void Open();
	void SaveAs();

	CTimer _timerhint;

	int _iTileSizeRatio1, _iTileSizeRatio2;

	CCheckMenuItem _displayscore, _displaybar, _displaymoves, _displaymovesstart, _displaymoveshere;
};

#endif