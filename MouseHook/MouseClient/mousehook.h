#ifdef HOOKAPI

#else

#define HOOKAPI extern "C" __declspec(dllimport)

#endif

#include <windows.h>

#define WM_MOUSEHOOK WM_USER + 1


HOOKAPI void InstallHook(HWND hWnd);
HOOKAPI void UninstallHook();