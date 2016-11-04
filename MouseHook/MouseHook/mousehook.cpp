#define HOOKAPI extern "C" __declspec(dllexport)
#include "mousehook.h"

#pragma data_seg(".bss")
HHOOK hHook;
HWND hWnd;
#pragma data_seg()
#pragma comment(linker, "/SECTION:.bss,S")

HINSTANCE hInstance;

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, PVOID lpvReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		hInstance = hInst;
	}
	return TRUE;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PMOUSEHOOKSTRUCT pMouseHookStruct = (PMOUSEHOOKSTRUCT) lParam;
	HWND hwnd;
	CallNextHookEx(hHook, nCode, wParam, lParam);
	hwnd = WindowFromPoint(pMouseHookStruct->pt);
	PostMessage(hWnd, WM_MOUSEHOOK, (WPARAM)hwnd, 0);
	return 0;
}

HOOKAPI void InstallHook(HWND hwnd)
{
	hWnd = hwnd;
	hHook = SetWindowsHookEx(WH_MOUSE, MouseProc, hInstance, 0);
}

HOOKAPI void UninstallHook()
{
	UnhookWindowsHookEx(hHook);
}