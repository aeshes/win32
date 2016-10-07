#include <windows.h>
#include "ui.h"

#define WM_KEYEVENT WM_USER + 1

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;

	switch (uMsg)
	{
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
	case WM_KEYEVENT:
		MessageBox(NULL, TEXT("Got message"), TEXT("YAY!"), MB_OK);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hMainWnd;
	MSG msg;

	RegisterWndClass(WndProc, TEXT("LogServer"), COLOR_WINDOW);
	hMainWnd = CreateWindow(TEXT("LogServer"), TEXT("LogServer"),
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, 300, 150, (HWND) NULL, (HMENU) NULL,
		(HINSTANCE)hInst, NULL);

	if (!hMainWnd)
	{
		MessageBox(NULL, TEXT("Cant create main window"), TEXT("Error"), MB_OK);
		return 0;
	}

	ShowWindow(hMainWnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}