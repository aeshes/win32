#include "registry.h"
#include <stdio.h>

BOOL CreateBinKey(char *branch, char *key, BYTE *value, DWORD size)
{
	HKEY hKey;

	if (RegCreateKeyEx(HKEY_CURRENT_USER,
		branch,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		NULL,
		&hKey,
		NULL) != ERROR_SUCCESS)
	{
		return FALSE;	// Error
	}
	else
	{
		if (RegSetValueEx(hKey, key, 0, REG_BINARY, value, size) != ERROR_SUCCESS)
			return FALSE;
		if (RegCloseKey(hKey) != ERROR_SUCCESS)
			return FALSE;
	}
	return TRUE;
}

BOOL GetBinKey(char *branch, char *key, BYTE *value, DWORD size)
{
	HKEY hKey;

	if (RegOpenKeyEx(HKEY_CURRENT_USER,
			branch,
			0,
			KEY_QUERY_VALUE | KEY_WOW64_32KEY,
			&hKey) == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(hKey,
				key,
				NULL,
				NULL,
				(LPBYTE)value,
				&size) != ERROR_SUCCESS)
		{
			return FALSE;
		}
	}
	else return FALSE;

	return TRUE;
}

BOOL CreateDwordKey(char *branch, char *key, DWORD value)
{
	return FALSE;
}

BOOL DeleteKey(char *branch, char *key)
{
	HKEY hKey;

	if (RegOpenKeyEx(HKEY_CURRENT_USER,
			branch,
			0,
			KEY_SET_VALUE | KEY_WOW64_32KEY,
			&hKey) != ERROR_SUCCESS)
	{
		return FALSE;
	}
	else
	{
		/*if (RegDeleteKeyEx(hKey, key, KEY_WOW64_32KEY, 0) != ERROR_SUCCESS)*/
		if (RegDeleteValue(hKey, key))
		{
			RegCloseKey(hKey);
			return FALSE;
		}
		RegCloseKey(hKey);
	}
	return TRUE;
}
