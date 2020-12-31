//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPMAIN.H
//
// Definitions for WPMainWin.

#ifndef WPMAIN_H
#define WPMAIN_H

#include "wpwin.h"

//////////////////
// Main application window.
// 
class WPMainWin : public WPWin {
public:
	WPMainWin(CSTR classnm="MAINWIN");
};

#endif
