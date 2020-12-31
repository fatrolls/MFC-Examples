//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: APP.CPP
//
// Sample program demonstrates how to build DLLs with classes.

#include "wppdll.h"

//////////////////
// Class is derived from base class in DLL.
// 
class Derived : public Base {
	void displayMsg()		{ DisplayMessage("Hello from APP!"); }
};

int PASCAL WinMain(HANDLE hinst, HANDLE pinst, LPSTR cmd, int show)
{
	Base baseClassInstance;			// create instance of base class
	Derived derivedClassInstance;	// create instance of derived class

	Base *p = &baseClassInstance;
	p->display();						// should invoke DLL
	p = &derivedClassInstance;
	p->display();						// should invoke APP
	
	return 0;
}
