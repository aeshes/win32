#include <windows.h>
#include <stdio.h>
#include "registry.h"

#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
	char key[] = "xyz";
	BYTE value[] = "123";
	char buffer[MAX_PATH];
	DWORD dwSize = 0;

	ZeroMemory(buffer, MAX_PATH);
	GetModuleFileName(GetModuleHandle(0), buffer, MAX_PATH);
	if (!CreateBinKey(AUTORUN_SUBKEY, key, buffer, lstrlen(buffer)))
	{
		MessageBox(NULL, TEXT("Error while CreateBinKey"), TEXT("Error"), MB_OK);
	}

	ZeroMemory(buffer, MAX_PATH);
	dwSize = 3;
	if (GetBinKey(AUTORUN_SUBKEY, key, buffer, MAX_PATH))
	{
		printf("%s\n", buffer);
	}
	else
	{
		MessageBox(NULL, TEXT("Error while GetBinKey"), TEXT("Error"), MB_OK);
	}
	DeleteKey(AUTORUN_SUBKEY, key);
	MessageBox(NULL, TEXT("KEK"), TEXT("OLOLO"), MB_OK);
}
