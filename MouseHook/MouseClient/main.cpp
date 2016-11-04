#include <windows.h>
#include "mousehook.h"
#include "ui.h"

#define ID_TEXTBOX_HWND		3000
#define ID_TEXTBOX_CLASS	3001
#define ID_TEXTBOX_WNDPROC	3002
#define ID_BUTTON_HOOK		3003

DWORD HookFlag = FALSE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hMainWnd;
	MSG msg;

	RegisterWndClass(WndProc, TEXT("Info"), COLOR_WINDOW);
	hMainWnd = CreateWindow(TEXT("Info"), TEXT("Info"),
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, 250, 130, (HWND)NULL, (HMENU)NULL,
		(HINSTANCE)hInstance, NULL);

	if (!hMainWnd)
	{
		MessageBox(NULL, TEXT("Can\'t create main window."), TEXT("Error"), MB_OK);
		return GetLastError();
	}

	ShowWindow(hMainWnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	TCHAR buffer[128];

	switch (uMsg)
	{
	case WM_CREATE:
		/* Create text box containing descriptor of current window */
		CreateWindow(TEXT("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE,
			10, 10, 120, 20, hWnd, (HMENU)ID_TEXTBOX_HWND, NULL, NULL);
		/* Create text box containing class name of current window */
		CreateWindow(TEXT("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE,
			10, 35, 120, 20, hWnd, (HMENU)ID_TEXTBOX_CLASS, NULL, NULL);
		/* Create text box containing address of WndProc of current window */
		CreateWindow(TEXT("EDIT"), NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE,
			10, 60, 120, 20, hWnd, (HMENU)ID_TEXTBOX_WNDPROC, NULL, NULL);
		/* Create button to install/uninstall mouse hook */
		CreateWindow(TEXT("BUTTON"), TEXT("Hook"), WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			150, 10, 60, 20, hWnd, (HMENU)ID_BUTTON_HOOK, NULL, NULL);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		if (ID_BUTTON_HOOK == wParam)
		{
			if (FALSE == HookFlag)
			{
				InstallHook(hWnd);
				HookFlag = TRUE;
				SetDlgItemText(hWnd, ID_BUTTON_HOOK, TEXT("Unhook"));
			}
			else
			{
				UninstallHook();
				HookFlag = FALSE;
				SetDlgItemText(hWnd, ID_BUTTON_HOOK, TEXT("Hook"));
				SetDlgItemText(hWnd, ID_TEXTBOX_HWND, NULL);
				SetDlgItemText(hWnd, ID_TEXTBOX_CLASS, NULL);
				SetDlgItemText(hWnd, ID_TEXTBOX_WNDPROC, NULL);
			}
		}
		break;
	case WM_MOUSEHOOK:
		wsprintf(buffer, TEXT("%lx"), wParam);	/* Get hwnd from message */
		SetDlgItemText(hWnd, ID_TEXTBOX_HWND, buffer);
		GetClassName((HWND)wParam, buffer, 128);	/* Get class name from hwnd */
		SetDlgItemText(hWnd, ID_TEXTBOX_CLASS, buffer);
		wsprintf(buffer, TEXT("%lx"), GetClassLong((HWND)wParam, GCL_WNDPROC));	/* Get address of WNDPROC from hwnd */
		SetDlgItemText(hWnd, ID_TEXTBOX_WNDPROC, buffer);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}