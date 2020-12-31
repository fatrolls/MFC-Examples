



#ifndef __MAIN_H__INCLUDED
#define __MAIN_H__INCLUDED

#define IDC_STATUS		110

#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ConfigureProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK ModifyUserProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgIPConfig(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgAddIP(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // __MAIN_H__INCLUDED




