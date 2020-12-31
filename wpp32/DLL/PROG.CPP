//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: PROG.CPP
//
// WinMain function calls MsgBox in DLL.
//
// New Windows 95 version: to test, run with args as in
//
// prog one two three

#include "msgbox.h"

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmd, int show)
{
	DisplayMessage("Hello from DLL!\nCommand line = \"%s\"\nshow = %d",
		cmd, show);
	return 0;
}
