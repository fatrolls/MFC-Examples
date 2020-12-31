//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPPDLL.CPP
//
// Sample program demonstrates how to build DLLs with classes.

#include "wppdll.h"
#include <stdio.h>
#include <stdarg.h>

//////////////////
// In Win32, DllMain replaces LibMain/WEP
//
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH) {

	} else if (dwReason == DLL_PROCESS_DETACH) {

	}
	return TRUE;
}

//////////////////
// Handy function for doing printf-style message boxes.
// 
int DLLFUNC DisplayMessage(const char* format, ...)
{
	char buf[128];

	va_list argptr;
	va_start(argptr, format);
	vsprintf(buf, format, argptr);
	va_end(argptr);
	return MessageBox(NULL, buf, "MsgBox", MB_OK | MB_ICONINFORMATION);
}

void Base::displayMsg()
{ 
	DisplayMessage("Hello from DLL!");
}

void Base::display()
{ 
	displayMsg();
}



