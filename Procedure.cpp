#include "procedure.h"
#include "lib\other\canvas.h"
#include "resource.h"
#include "main.h"

BOOL CALLBACK SimpleDlgProc(HWND hwnd, UINT message, UINT wParam, LPARAM lParam);

void CProcedure::Create(CREATESTRUCT* create)
{
	_world = new CWorld;
	_view.Create(create->hInstance, _world);
}

bool CProcedure::Paint(HDC hdc)
{
	PaintCanvas canvas(_hwnd);
	_view.Paint(canvas);

	return true;
}

bool CProcedure::Size(int width, int height)
{
	_view.Size(width, height);
	UpdateAndPaint();

	return true;
}

bool CProcedure::LeftClick(int x, int y)
{
	return true;
}

bool CProcedure::MenuCommand (int cmdId, bool isAccel)
{
	switch(cmdId)
	{
	case IDM_FILE_NEW:
		_world->New();
		return true;
	case ID_HELP_ABOUT:
		DialogBox(GetModuleHandle(NULL), (char*)IDD_ABOUT, _hwnd, DLGPROC(SimpleDlgProc));
		return true;

	default:
		return false;
	}
}

void CProcedure::UpdateAndPaint()
{
	UpdateCanvas canvas(_hwnd);
	_view.Update(canvas);
	InvalidateRect(_hwnd, NULL, 0);
}

BOOL CALLBACK SimpleDlgProc
   (HWND hwnd, UINT message, UINT wParam, LPARAM lParam)
{
	RECT rect, rect2;

    switch (message)
    {
    case WM_INITDIALOG:
		// Center dialog
		GetWindowRect(GetParent(hwnd), &rect);
		GetWindowRect(hwnd , &rect2);
		SetWindowPos (hwnd, HWND_TOP, ((rect.left + rect.right) / 2) - ((rect2.right - rect2.left) / 2), ((rect.top + rect.bottom) / 2) - ((rect2.bottom - rect2.top) / 2), 0, 0, SWP_NOSIZE);
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        case IDCANCEL:
            EndDialog(hwnd, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}
