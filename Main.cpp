#include <windows.h>

#include "lib/app.h"
#include "procedure.h"
#include "resource.h"

#include "main.h"

LRESULT CALLBACK CClass::Procedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	char * szClassName = "CWindow";
	char * szCaption   = "Radial Pong";

	CClass windowclass (szClassName, hInstance);
	windowclass.SetMenu(IDR_MENU);
	// windowclass.SetIcon(IDI_ICON);
	windowclass.Register();

	CProcedure proc;

	CWindow window(szCaption, szClassName, hInstance);
	window.SetStyle(WINDOW_STYLE);
	window.SetDimentions(GAME_WIDTH, GAME_HEIGHT, true);
	window.Create(&proc);
	// window.AttachAccelerator(IDR_ACCELERATOR);
	window.Show();

	DWORD dwStartTime = GetTickCount();
	while(window.ProcessMessage())
	{
		if (GetTickCount() - dwStartTime > 15)
		{
			// Clear back
			if (proc._world->IsPlaying())
				proc._world->Turn();
			proc.UpdateAndPaint();

			// Update start time
			dwStartTime = GetTickCount();
		}
	}

	return 0;
}
