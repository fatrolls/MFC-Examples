// altest.cpp : Defines the entry point for the application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	MessageBox(GetDesktopWindow(), lpCmdLine, "AutoLaunch Test Applet", MB_OK);

	return 0;
}



