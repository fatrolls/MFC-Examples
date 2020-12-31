#pragma once
#undef UNICODE
#include <windows.h>
#include <cstdio>
#include <vector>
#include <cstring>
#include "resource.h"
using std::vector;
using std::string;

BOOL CALLBACK DlgProc(HWND hDlg, UINT uiMsg, WPARAM wPARAM, LPARAM lParam);
void CheckAndUpdateComboBox(HWND hDlg);
void ParseAndStoreEmail(SOCKET, const char*);
int SearchForDuplicates(SOCKET, string);
string GetEmailFromSession(SOCKET);
SOCKET GetSessionFromEmail(string);
void BuildPacket(SOCKET, const char*);