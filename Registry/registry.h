#ifndef REGISTRY_H
#define REGISTRY_H

#include <windows.h>
#include <strsafe.h>

#define DEFAULT_SUBKEY "Software\\ZerochanLocker"
#define AUTORUN_SUBKEY "Software\\Microsoft\\Windows\\CurrentVersion\\Run"

BOOL CreateBinKey(char *branch, char *key, BYTE *value, DWORD dwSize);
BOOL CreateDwordKey(char *branch, char *key, DWORD value);
BOOL GetBinKey(char *branch, char *key, BYTE *buffer, DWORD dwSize);
BOOL DeleteKey(char *branch, char *key);

#endif
