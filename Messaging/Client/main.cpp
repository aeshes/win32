#include <windows.h>

#define WM_KEYEVENT WM_USER + 1

int main(int argc, char *argv[])
{
	HWND hServerWnd = FindWindow(NULL, TEXT("LogServer"));

	for (int i = 0; i < 3; i++)
	{
		PostMessage(hServerWnd, WM_KEYEVENT, 0, 0);
	}
	return 0;
}